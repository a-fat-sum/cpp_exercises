# Inheritance in C++ (Interview Guide)

Focus: polymorphism, virtual tables, and construction/destruction order.

## 1) Core inheritance syntax

```cpp
class Base {
public:
    virtual ~Base() = default;
    virtual void speak() const {}
};

class Derived : public Base {
public:
    void speak() const override {}
};
```

### Interview points
- `public` inheritance models “is-a”
- mark overridden functions with `override`
- use virtual destructor in polymorphic base classes

---

## 2) Virtual dispatch and vtable intuition

- If a class has virtual functions, objects usually carry a hidden vptr.
- vptr points to a vtable containing function pointers for that dynamic type.
- Calls through base reference/pointer resolve at runtime.

```cpp
Base* p = new Derived();
p->speak(); // calls Derived::speak()
delete p;   // safe because Base destructor is virtual
```

Interview caveat: exact vtable layout is implementation-defined.

---

## 3) Construction order in inheritance

### Rules
1. Base class subobject constructed first
2. Then members of derived class (declaration order)
3. Then derived class constructor body

```cpp
#include <iostream>

struct Base {
    Base() { std::cout << "Base ctor\n"; }
    virtual ~Base() { std::cout << "Base dtor\n"; }
};

struct Member {
    Member() { std::cout << "Member ctor\n"; }
    ~Member() { std::cout << "Member dtor\n"; }
};

struct Derived : Base {
    Member m;
    Derived() { std::cout << "Derived ctor\n"; }
    ~Derived() override { std::cout << "Derived dtor\n"; }
};

int main() {
    Derived d;
}
```

Output order:
1. `Base ctor`
2. `Member ctor`
3. `Derived ctor`
4. `Derived dtor`
5. `Member dtor`
6. `Base dtor`

Destruction is reverse of construction.

---

## 4) What happens with virtual calls in constructors/destructors?

During base construction/destruction, dynamic dispatch to most-derived type is not active.

```cpp
#include <iostream>

struct Base {
    Base() { f(); }
    virtual void f() { std::cout << "Base::f\n"; }
    virtual ~Base() { f(); }
};

struct Derived : Base {
    void f() override { std::cout << "Derived::f\n"; }
};
```

`Base` constructor/destructor call `Base::f`, not `Derived::f`.

Interview takeaway: avoid calling virtuals in ctors/dtors.

---

## 5) Object slicing

```cpp
#include <vector>

struct Base {
    virtual ~Base() = default;
    virtual int id() const { return 0; }
};

struct Derived : Base {
    int id() const override { return 1; }
};

Base b = Derived{}; // slicing
```

- Derived-specific part is sliced away in by-value base copy.
- Use references/pointers for polymorphism.

---

## 6) Access control and inheritance modes

- `public` inheritance: public/protected keep their access (for is-a)
- `protected` inheritance: public/protected become protected
- `private` inheritance: public/protected become private

Most OOP polymorphic hierarchies use `public` inheritance.

---

## 7) Multiple inheritance basics

- Can model orthogonal interfaces (`class X : public IA, public IB`)
- Can cause ambiguity (`Base` appears more than once)
- virtual inheritance solves diamond shared-base duplication

Interview expectation: know tradeoffs, not memorize ABI details.

---

## 8) `final`, `override`, and interface-style bases

```cpp
struct IShape {
    virtual ~IShape() = default;
    virtual double area() const = 0;
};

struct Circle final : IShape {
    double r;
    explicit Circle(double radius) : r(radius) {}
    double area() const override { return 3.14159 * r * r; }
};
```

- pure virtual (`= 0`) makes abstract base/interface-like type
- `final` prevents further overriding or derivation

---

## 9) Composition vs inheritance (common interview discussion)

Prefer composition unless inheritance clearly models substitutability.

Use inheritance when:
- dynamic polymorphism is required
- stable interface with varying implementations

Use composition when:
- reuse behavior without tight coupling
- avoid fragile base-class problems

---

## 10) Interview rapid-fire questions

1. Why should polymorphic base classes have virtual destructors?
2. What is object slicing and how do you avoid it?
3. What is the order of construction/destruction for derived objects?
4. Why are virtual calls in constructors dangerous/misleading?
5. In practice, when do you choose composition over inheritance?

# Modern C++ Concepts (Interview Notes)

This guide focuses on practical C++17/20 concepts interviewers often ask about.

## 1) Value categories, move semantics, and perfect forwarding

### Key terms
- **lvalue**: has identity (named object)
- **rvalue**: temporary value
- **xvalue/prvalue**: finer categories of rvalues

### Why it matters
Move semantics avoids deep copies for expensive objects (`std::string`, `std::vector`, custom resources).

```cpp
#include <vector>
#include <string>

std::vector<std::string> makeNames() {
    std::vector<std::string> v;
    v.push_back("Alice");
    v.push_back("Bob");
    return v; // NRVO or move
}
```

### Interview points
- Rule of 0/3/5
- `std::move` casts to rvalue reference; it does not move by itself
- moved-from objects must remain valid but are in unspecified state
- use `std::forward<T>(x)` only in forwarding references (`T&&` in templates)

---

## 2) RAII and smart pointers

### Smart pointer quick comparison
- `std::unique_ptr<T>`: exclusive ownership, lightweight, default choice
- `std::shared_ptr<T>`: shared ownership with ref-count overhead
- `std::weak_ptr<T>`: non-owning observer to break ownership cycles

```cpp
#include <memory>

struct Node {
    std::unique_ptr<Node> next;
};

auto n = std::make_unique<Node>();
```

### Interview pitfalls
- avoid raw `new`/`delete` in application code
- prefer `std::make_unique` / `std::make_shared`
- cyclical `shared_ptr` references leak unless one side is `weak_ptr`

---

## 3) Structured bindings and tuple-like interfaces

```cpp
#include <tuple>
#include <map>

std::tuple<int, double> f() { return {42, 3.14}; }

auto [i, d] = f();

std::map<int, int> m{{1,10}, {2,20}};
for (const auto& [k, v] : m) {
    // use k, v
}
```

### Interview points
- binds by value unless references are used:
  - `auto [a, b] = pair;` copies
  - `auto& [a, b] = pair;` binds by reference

---

## 4) `auto`, `decltype`, `decltype(auto)`

- `auto` drops references/top-level const in many contexts
- `decltype(expr)` keeps exact type category
- `decltype(auto)` preserves references in return types

```cpp
int x = 10;
int& rx = x;
auto a = rx;        // int
decltype(rx) b = x; // int&
```

---

## 5) Lambdas

### Capture essentials
- `[=]` by value, `[&]` by reference
- `[this]` captures `this` pointer
- `[x = std::move(obj)]` init-capture (move into lambda)

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v{1,2,3};
int sum = 0;
std::for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
```

### Interview points
- generic lambdas (`auto` params)
- closure type is unique and unnamed
- capture lifetime pitfalls (dangling references)

---

## 6) `constexpr`, `consteval`, and `constinit`

- `constexpr`: can be compile-time if inputs are constant
- `consteval`: must be compile-time
- `constinit`: static storage object is initialized at compile time

```cpp
constexpr int square(int x) { return x * x; }
static_assert(square(5) == 25);
```

---

## 7) Templates, concepts, and SFINAE

### Concepts (C++20)

```cpp
#include <concepts>

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

template <Addable T>
T add(T a, T b) { return a + b; }
```

### Interview points
- concepts improve diagnostics vs old SFINAE-heavy style
- watch code bloat due to many instantiations

---

## 8) `std::optional`, `std::variant`, `std::any`

- `optional<T>`: maybe-value, avoids sentinel values
- `variant<A,B,...>`: type-safe union; use `std::visit`
- `any`: type-erased box with runtime checks

```cpp
#include <optional>

std::optional<int> parsePositive(int x) {
    if (x > 0) return x;
    return std::nullopt;
}
```

---

## 9) Ranges (C++20)

```cpp
#include <ranges>
#include <vector>

std::vector<int> v{1,2,3,4,5,6};
auto even = v | std::views::filter([](int n){ return n % 2 == 0; })
              | std::views::transform([](int n){ return n * n; });
```

### Interview points
- views are lazy
- know when to materialize to container

---

## 10) Concurrency primitives (high level)

- `std::thread`, `std::jthread` (C++20)
- mutexes: `std::mutex`, `std::scoped_lock`
- atomics: `std::atomic<T>` for lock-free style on small operations
- condition variables for producer/consumer

---

## 11) Memory model basics

- Data race = undefined behavior
- Atomic operations can define synchronization and ordering
- Common orderings: `seq_cst` (default), `acquire/release`, `relaxed`

Interview tip: explain **happens-before** in simple words.

---

## 12) Exception safety levels

- basic guarantee: no leaks, valid state
- strong guarantee: commit-or-rollback
- no-throw guarantee

`noexcept` can improve move performance in containers.

---

## 13) Common “what would you choose?” interview questions

- `vector` vs `list` (cache locality often favors `vector`)
- `emplace_back` vs `push_back`
- inheritance vs composition
- virtual dispatch cost and alternatives (`std::variant`, CRTP, templates)

---

## 14) Frequently asked pitfalls

- object slicing with base-by-value
- missing virtual destructor in polymorphic base class
- dangling references in lambdas/ranges
- signed/unsigned comparison bugs
- undefined behavior from invalidated iterators

---

## 15) Fast revision checklist

- Can you explain Rule of 0/3/5 with an example?
- Can you write a move constructor correctly?
- Can you explain `unique_ptr` vs `shared_ptr` tradeoffs?
- Can you show structured binding by reference?
- Can you explain why `vector` is often faster than `list`?
- Can you describe one race condition and how to fix it?

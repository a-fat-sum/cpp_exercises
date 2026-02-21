# Threading in C++ (Interview Rundown)

This is a practical primer for `std::thread` and related synchronization tools.

## 1) Creating and joining threads

```cpp
#include <thread>
#include <iostream>

void worker(int id) {
    std::cout << "Worker " << id << "\n";
}

int main() {
    std::thread t1(worker, 1);
    t1.join(); // always join or detach before destruction
}
```

### Interview points
- destroying a joinable `std::thread` calls `std::terminate`
- prefer RAII wrappers or `std::jthread` in C++20

---

## 2) `std::jthread` and cooperative cancellation (C++20)

`std::jthread` auto-joins in destructor and supports stop tokens.

```cpp
#include <thread>
#include <chrono>

void loop(std::stop_token st) {
    while (!st.stop_requested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::jthread t(loop);
    // destructor requests stop + joins
}
```

---

## 3) Mutexes and lock guards

```cpp
#include <mutex>
#include <thread>
#include <vector>

std::mutex m;
int counter = 0;

void inc() {
    std::lock_guard<std::mutex> lock(m);
    ++counter;
}
```

### Best practices
- lock as late as possible, unlock as early as possible
- use RAII (`lock_guard`, `scoped_lock`, `unique_lock`)
- avoid manual `lock()`/`unlock()` unless necessary

---

## 4) Avoiding deadlocks

- always lock multiple mutexes in consistent order
- or use `std::scoped_lock(m1, m2)` to lock atomically

```cpp
std::mutex a, b;

void safe() {
    std::scoped_lock lock(a, b);
    // critical section
}
```

---

## 5) Condition variables (producer/consumer)

```cpp
#include <condition_variable>
#include <mutex>
#include <queue>

std::mutex m;
std::condition_variable cv;
std::queue<int> q;
bool done = false;

void producer() {
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(42);
    }
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return !q.empty() || done; });
    if (!q.empty()) {
        int value = q.front();
        q.pop();
    }
}
```

### Interview points
- use predicate with `wait` to handle spurious wakeups
- modify shared state under lock, then notify

---

## 6) Atomics

```cpp
#include <atomic>

std::atomic<int> count{0};

void work() {
    count.fetch_add(1, std::memory_order_relaxed);
}
```

### When to use
- simple shared counters/flags
- low-level lock-free algorithms (advanced)

### Memory order quick guide
- `seq_cst`: easiest mental model, strongest ordering
- `acquire/release`: common for synchronization
- `relaxed`: atomicity only, no ordering guarantees

Interview tip: if unsure, start with default `seq_cst` for correctness.

---

## 7) `std::async`, futures, promises

```cpp
#include <future>

int compute() { return 7; }

int main() {
    auto fut = std::async(std::launch::async, compute);
    int result = fut.get();
}
```

- `future.get()` blocks and retrieves result/exception
- `promise` can manually set value for a `future`

---

## 8) Common interview pitfalls

- data races from unsynchronized shared state
- capturing references in thread lambdas that outlive scope
- holding lock while doing slow I/O
- forgetting to join/detach thread
- assuming atomics replace all locking needs

---

## 9) Questions interviewers ask

1. Difference between thread safety and reentrancy?
2. Why can condition variable wake up spuriously?
3. `lock_guard` vs `unique_lock`?
4. When would you choose atomics over mutex?
5. How would you design a thread-safe queue?

---

## 10) Quick checklist

- Can you create, join, and safely stop a worker thread?
- Can you explain race conditions with one real example?
- Can you write producer/consumer with a condition variable?
- Can you explain when `atomic<int>` is enough and when it is not?

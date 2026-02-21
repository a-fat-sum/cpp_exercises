# C++ Exceptions: Quick Basics

## What an exception is
An exception is a runtime error signal that transfers control to the nearest matching `catch` block.

```cpp
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("b must not be zero");
    }
    return a / b;
}
```

## Basic flow (`try` / `throw` / `catch`)

```cpp
try {
    int x = divide(10, 0);
} catch (const std::invalid_argument& ex) {
    // handle bad argument
} catch (const std::exception& ex) {
    // fallback for most standard exceptions
}
```

- `throw` creates/propagates an exception object.
- Stack unwinding destroys local objects, so RAII cleanup still runs.
- Prefer catching by `const&` to avoid slicing/copies.

## Common standard exception types
- `std::exception`: base class for standard exceptions.
- `std::runtime_error`: runtime failures (generic runtime issues).
- `std::logic_error`: programming/logic mistakes category.
- `std::invalid_argument`: bad function argument.
- `std::out_of_range`: index/key out of valid range.
- `std::length_error`: requested size too large.
- `std::overflow_error` / `std::underflow_error`: arithmetic overflow/underflow.
- `std::bad_alloc`: memory allocation failed.

## When to throw (rule of thumb)
Good candidates:
- Broken preconditions that caller should handle.
- Failures that prevent continuing current operation safely.

Less ideal:
- Normal control flow (exceptions should be exceptional).
- Tight loops where failure is expected frequently.

## Embedded / low-level environments: why exceptions are often disabled
Some embedded projects compile with exceptions off (e.g., `-fno-exceptions`) because they may want:
- Smaller binary size.
- More predictable timing/latency.
- Simpler certification/safety analysis.

In those environments, teams often use:
- Error codes / status enums.
- `std::optional` / `std::expected`-style returns.
- Centralized fault handlers.

## Interview tips
- Explain that RAII makes exceptions safer (automatic cleanup during unwinding).
- Mention exception safety levels:
  - basic guarantee (no leaks, valid state),
  - strong guarantee (commit-or-rollback),
  - no-throw guarantee.
- Mention that `noexcept` helps optimization and is important for move operations.

## Practical best practices
- Throw specific exception types, not raw strings.
- Add clear messages (`what()` should be meaningful).
- Catch at the right level (where you can recover).
- Avoid swallowing exceptions silently.

## `noexcept`: what it is and when to use it

`noexcept` marks a function as non-throwing.

```cpp
void cleanup() noexcept {
    // must not throw
}
```

### What it means in practice
- If an exception escapes a `noexcept` function, the program calls `std::terminate`.
- So use it only when you are confident the function cannot throw (or you handle internally).

### Why it matters
- It documents intent: “this function should not fail by exception.”
- It can enable compiler/library optimizations.
- Standard containers prefer `noexcept` move operations during reallocation (important performance point).

### Common places to use `noexcept`
- Destructors (they are implicitly non-throwing by default in modern C++ unless specified otherwise).
- Move constructor / move assignment when operations are truly non-throwing.
- Small utility functions that cannot throw.
- `swap` implementations that are non-throwing.

### Places to avoid `noexcept`
- Functions that may allocate and can naturally fail with exceptions.
- Code paths that call other potentially-throwing operations unless you handle exceptions internally.

### Interview one-liner
Use `noexcept` for operations that are logically non-throwing—especially move/swap/destructors—because it improves correctness contracts and often improves container behavior/performance.

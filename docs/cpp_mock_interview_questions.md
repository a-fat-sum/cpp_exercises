# C++ Mock Interview Questions (with Expected Answer Points)

Use this as a rapid-fire practice sheet. Try answering aloud in 30–90 seconds each.

## 1) Language fundamentals

1. What is the difference between a declaration and a definition?
   - Declaration introduces a name/type/signature.
   - Definition allocates storage or provides full implementation.

2. What is undefined behavior in C++?
   - Program behavior is not prescribed by standard.
   - Compiler may optimize aggressively; results can vary wildly.

3. Difference between `const` and `constexpr`?
   - `const`: read-only after initialization.
   - `constexpr`: potentially compile-time constant/expression.

4. What is `consteval`?
   - Function must be evaluated at compile time.

5. What is `constinit`?
   - Ensures static/thread storage object is initialized at compile time.

6. What are lvalues and rvalues?
   - lvalue: has identity/location.
   - rvalue: temporary/non-persistent value.

7. What does `std::move` do?
   - Casts expression to rvalue reference.
   - Enables move overloads; does not move by itself.

8. What is perfect forwarding?
   - Preserving value category using forwarding reference + `std::forward`.

9. Difference between copy constructor and copy assignment?
   - Copy constructor creates new object.
   - Copy assignment overwrites existing object.

10. Rule of 3/5/0?
   - If managing resources, define/correctly handle special member functions.
   - Prefer Rule of 0 by using RAII types.

## 2) OOP and inheritance

11. Why should polymorphic base classes have virtual destructors?
   - So deleting via base pointer calls derived destructor correctly.

12. What is object slicing?
   - Assigning/copying derived object into base by value loses derived part.

13. Explain `override` and `final`.
   - `override` checks matching virtual signature.
   - `final` prevents further overriding/derivation.

14. What is a pure virtual function?
   - Declared with `= 0`; makes class abstract.

15. Constructor order in inheritance?
   - Base first, then members (declaration order), then derived body.

16. Destruction order in inheritance?
   - Reverse of construction: derived, members, then base.

17. Why avoid virtual calls in constructors/destructors?
   - Dynamic dispatch to most-derived is not active there.

18. Composition vs inheritance?
   - Prefer composition unless true “is-a” polymorphic relationship exists.

19. What is multiple inheritance risk?
   - Ambiguity/diamond complexity; virtual inheritance may be required.

20. What is a vtable (conceptually)?
   - Implementation mechanism for runtime virtual dispatch (ABI-specific).

## 3) Memory and resource management

21. `unique_ptr` vs `shared_ptr`?
   - `unique_ptr`: single owner, lightweight.
   - `shared_ptr`: shared ownership with atomic ref counting overhead.

22. Why use `weak_ptr`?
   - Non-owning reference to break `shared_ptr` cycles.

23. Why prefer `make_unique`/`make_shared`?
   - Exception safety and concise allocation patterns.

24. What is RAII?
   - Resource acquisition in constructor, release in destructor.

25. What is a memory leak?
   - Allocated resource no longer reachable/released.

26. What is a dangling pointer/reference?
   - Points/refers to object whose lifetime has ended.

27. Stack vs heap allocation?
   - Stack: automatic storage, fast lifetime management.
   - Heap: dynamic lifetime/size, manual/owned management.

28. What are common allocator-aware containers?
   - `std::vector`, `std::string`, associative containers.

29. What invalidates iterators in `vector`?
   - Reallocation on growth, erase/insert shifts.

30. Why is `vector` often faster than `list`?
   - Cache locality and contiguous storage.

## 4) Templates and modern features

31. What is template instantiation?
   - Compiler generates concrete code per used type arguments.

32. What is SFINAE?
   - Substitution failure removes invalid overloads from resolution.

33. Why are concepts useful?
   - Better constraints and diagnostics than raw SFINAE.

34. What are structured bindings?
   - Destructure tuple-like/pair/aggregate into named bindings.

35. `auto` vs `decltype(auto)`?
   - `auto` may drop references.
   - `decltype(auto)` preserves exact type category.

36. What is `std::optional` for?
   - Represent maybe-present value without sentinel hacks.

37. `std::variant` vs polymorphism?
   - Variant: closed set of types, static visitation.
   - Polymorphism: open hierarchy, dynamic dispatch.

38. What is `std::any`?
   - Type-erased container holding one value of any copyable type.

39. What are ranges/views?
   - Composable lazy pipelines over sequences.

40. When can `emplace_back` help vs `push_back`?
   - In-place construction may avoid temporary object creation.

## 5) Concurrency and threading

41. What is a data race?
   - Unsynchronized conflicting access (at least one write) to same memory.

42. `mutex` vs `atomic`?
   - `mutex`: protects compound critical sections.
   - `atomic`: safe single-variable atomic operations.

43. Why use condition variables?
   - Efficient waiting for state change without busy spinning.

44. Why use predicate in `cv.wait`?
   - Handles spurious wakeups and re-checks condition safely.

45. `lock_guard` vs `unique_lock`?
   - `lock_guard`: minimal RAII lock.
   - `unique_lock`: movable, unlock/relock, needed for condition variables.

46. What is deadlock and one prevention method?
   - Circular waiting on locks; enforce lock ordering or `scoped_lock`.

47. What is `std::jthread` advantage over `std::thread`?
   - Auto-join and built-in cooperative cancellation support.

48. What is memory ordering in atomics?
   - Defines synchronization/order guarantees (`seq_cst`, acquire/release, relaxed).

49. What is false sharing?
   - Threads modify different variables on same cache line causing contention.

50. Why can destroying joinable `std::thread` terminate program?
   - Standard mandates `std::terminate` if thread not joined/detached.

## 6) Design, quality, and practical interview discussion

51. What is exception safety basic vs strong guarantee?
   - Basic: no leaks/valid state.
   - Strong: operation commits fully or has no effect.

52. Why mark move operations `noexcept` when possible?
   - Enables optimized moves in containers during reallocation.

53. Pimpl idiom: why use it?
   - Reduces compile dependencies and stabilizes ABI boundaries.

54. What is the One Definition Rule (ODR)?
   - Entities requiring single definition across program must obey ODR.

55. Header guards vs `#pragma once`?
   - Both prevent multiple inclusion; `#pragma once` is non-standard but widely supported.

56. How to reduce compile times in large C++ codebases?
   - Minimize includes, forward declare, isolate templates, use modules/PCH where suitable.

57. How do you profile before optimizing?
   - Measure hotspots with profiler; avoid premature optimization.

58. How would you design a thread-safe queue?
   - Mutex + condition variable + bounded/unbounded policy + clean shutdown semantics.

59. How do you decide between runtime and compile-time polymorphism?
   - Runtime for extensibility; compile-time for zero-overhead static dispatch.

60. What makes code “modern C++” in practice?
   - RAII-first ownership, value semantics where practical, smart pointers, strong typing, STL algorithms/ranges, careful concurrency primitives.

---

## Practice format suggestion

For each question:
1. Give a one-sentence answer.
2. Add one code-level example.
3. Mention one pitfall.
4. Mention one tradeoff.

If you can do that consistently, your interview responses will sound clear and senior.

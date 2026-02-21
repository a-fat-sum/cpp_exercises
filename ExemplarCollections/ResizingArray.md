# ResizingArray (Vector-like Dynamic Array)

## What it is
A contiguous dynamic array that grows when capacity is exhausted. This is the classic building block behind many high-performance containers.

## When to use
- Frequent append (`push_back`) operations.
- Fast random access by index.
- When cache locality matters.

## Core complexity
- Access by index: **O(1)**
- `push_back` (amortized): **O(1)**
- Growth reallocation step: **O(n)**
- Insert/erase in middle: **O(n)**

## Interview talking points
- Explain amortized analysis: occasional expensive resize is spread over many cheap inserts.
- Explain doubling strategy (`cap *= 2`) and why it is common.
- Mention cache locality advantage over linked structures.
- Discuss iterator/reference invalidation on reallocation.

## Modern C++ features shown
- Rule of 5 with move operations.
- `std::unique_ptr<T[]>` ownership.
- Perfect-forwarding style `emplace_back`.
- `[[nodiscard]]` for query methods.

## Common pitfalls
- Forgetting strong exception safety during reallocation.
- Returning references to invalidated memory after growth.
- Confusing `size` (used elements) vs `capacity` (allocated slots).

## Minimal usage
```cpp
#include "ResizingArray.h"

exemplar::ResizingArray<int> arr;
arr.push_back(10);
arr.push_back(20);
int x = arr[1]; // 20
```

## Good interview follow-up question
“How would you add iterator support and maintain exception safety guarantees?”

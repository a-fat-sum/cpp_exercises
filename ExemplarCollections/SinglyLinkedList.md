# SinglyLinkedList

## What it is
A node-based container where each node points to the next node only.

## When to use
- Frequent insertion/removal at the front.
- You do not need random index access.
- You want stable node addresses during growth.

## Core complexity
- `push_front`: **O(1)**
- `push_back`: **O(1)** (with tail pointer)
- `pop_front`: **O(1)**
- Search: **O(n)**

## Interview talking points
- Contrast with dynamic arrays: no contiguous memory, but no large reallocations.
- Show how `tail` pointer changes append from O(n) to O(1).
- Explain memory overhead per node (pointer + allocator metadata).

## Modern C++ features shown
- Ownership via `std::unique_ptr` in nodes.
- `std::optional` for maybe-found values.
- Rule-of-5 via copy-swap and defaulted moves.

## Common pitfalls
- Not updating `tail` correctly after popping last node.
- Memory leaks with raw pointers (avoided here via `unique_ptr`).
- Assuming good cache locality (linked nodes are scattered).

## Minimal usage
```cpp
#include "SinglyLinkedList.h"

exemplar::SinglyLinkedList<int> list;
list.push_front(3);
list.push_back(7);
bool has7 = list.contains(7);
```

## Good interview follow-up question
“How would you add an iterator without exposing node internals?”

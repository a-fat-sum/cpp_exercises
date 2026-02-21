# DoublyLinkedList

## What it is
A linked structure where each node stores pointers to both previous and next nodes.

## When to use
- You need fast insertion/removal at both ends.
- You need bidirectional traversal.
- Random indexing is not required.

## Core complexity
- `push_front`, `push_back`: **O(1)**
- `pop_front`, `pop_back`: **O(1)**
- Search: **O(n)**

## Interview talking points
- Compare with singly linked list: extra pointer gives reverse traversal and cheap back removal.
- Highlight memory overhead: two links per node.
- Mention invalidation differences vs contiguous containers.

## Modern C++ features shown
- Move constructor/assignment for ownership transfer.
- Copy-swap assignment for strong exception-safety style.
- `noexcept` where appropriate.

## Common pitfalls
- Not fixing both neighboring links during erase.
- Forgetting boundary cases (size 0/1).
- Iterator invalidation assumptions copied from `std::vector`.

## Minimal usage
```cpp
#include "DoublyLinkedList.h"

exemplar::DoublyLinkedList<int> list;
list.push_back(10);
list.push_front(5);
list.pop_back();
```

## Good interview follow-up question
“How would you add an `erase(node*)` operation safely?”

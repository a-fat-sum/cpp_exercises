# Queue (FIFO)

## What it is
A first-in-first-out container: oldest inserted element is removed first.

## When to use
- Task scheduling.
- Breadth-first search (BFS).
- Producer/consumer style pipelines.

## Core complexity
- `enqueue`: **O(1)**
- `dequeue`: **O(1)**
- `front`: **O(1)**

## Interview talking points
- Explain FIFO with a concrete timeline example.
- Show difference from stack (LIFO).
- Mention practical implementation choices: linked list vs circular buffer.

## Modern C++ features shown
- Move-aware enqueue overloads.
- Rule-of-5 support with explicit move operations.
- `noexcept` on non-throwing helpers.

## Common pitfalls
- Dequeuing from empty queue.
- Not clearing tail when last node removed.
- Using queue when random access is required.

## Minimal usage
```cpp
#include "Queue.h"

exemplar::Queue<int> q;
q.enqueue(1);
q.enqueue(2);
q.dequeue(); // removes 1
```

## Good interview follow-up question
“How would you implement a lock-free queue at a high level?”

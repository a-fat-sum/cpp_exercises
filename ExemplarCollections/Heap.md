# Heap (Binary Heap)

## What it is
A complete binary tree usually stored in an array where parent/child index math is cheap.

## When to use
- Repeatedly need smallest/largest element quickly.
- Priority scheduling.
- Building efficient top-k logic.

## Core complexity
- `top`: **O(1)**
- `push`: **O(log n)**
- `pop`: **O(log n)**
- Build from arbitrary array (if implemented with heapify): **O(n)**

## Interview talking points
- Explain array index mapping: `left=2i+1`, `right=2i+2`, `parent=(i-1)/2`.
- Explain why heap is not fully sorted.
- Contrast with BST: heap gives best root priority, BST gives ordered traversal.

## Modern C++ features shown
- Comparator-based customization (`Compare`).
- `emplace` with perfect forwarding.
- Exception-safe boundary checks.

## Common pitfalls
- Incorrect comparator direction (min-heap vs max-heap confusion).
- Off-by-one index errors in sift operations.
- Assuming search for arbitrary value is fast (it is O(n)).

## Minimal usage
```cpp
#include "Heap.h"

exemplar::Heap<int> heap;
heap.push(5);
heap.push(2);
heap.push(8);
int smallest = heap.top(); // 2
```

## Good interview follow-up question
“How would you implement `decrease_key` and why is it useful in Dijkstra?”

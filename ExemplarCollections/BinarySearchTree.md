# BinarySearchTree (BST)

## What it is
A binary tree with ordering invariant:
- Left subtree contains smaller keys.
- Right subtree contains larger keys.

## When to use
- You need ordered data and tree-style traversal.
- You want simpler pedagogical ordered set/map behavior.
- You can tolerate worst-case degradation without balancing.

## Core complexity (unbalanced BST)
- Search/Insert/Delete average: **O(log n)**
- Search/Insert/Delete worst-case: **O(n)**

## Interview talking points
- Explain in-order traversal producing sorted order.
- Explain worst-case degeneration (sorted input -> linked-list shape).
- Mention balanced alternatives: AVL, Red-Black, Treap.

## Modern C++ features shown
- Recursive ownership via `std::unique_ptr` children.
- `std::optional` for maybe-existing min/max.
- Comparator template parameter (`Compare`).

## Common pitfalls
- Incorrect delete for node with two children.
- Forgetting to update size during erase.
- Treating duplicate keys without a clear policy.

## Minimal usage
```cpp
#include "BinarySearchTree.h"

exemplar::BinarySearchTree<int> bst;
bst.insert(10);
bst.insert(4);
bst.insert(18);
auto sorted = bst.in_order();
```

## Good interview follow-up question
“How would you augment each node to support order-statistics (k-th smallest)?”

# Stack (LIFO)

## What it is
A last-in-first-out container: most recently added element is removed first.

## When to use
- DFS traversal.
- Undo/redo behavior.
- Expression evaluation and parser helpers.

## Core complexity
- `push`: **O(1)** amortized (array-backed)
- `pop`: **O(1)**
- `top`: **O(1)**

## Interview talking points
- Explain LIFO with call-stack analogy.
- Discuss array-backed vs linked-list-backed stack tradeoffs.
- Mention composition choice (`Stack` built on `ResizingArray`).

## Modern C++ features shown
- Perfect-forwarding `emplace`.
- Composition and value semantics.
- Exception-safe boundary checks.

## Common pitfalls
- Popping empty stack.
- Assuming iteration order equals insertion order.
- Ignoring growth strategy if array-backed.

## Minimal usage
```cpp
#include "Stack.h"

exemplar::Stack<int> st;
st.push(10);
st.push(20);
int top = st.top(); // 20
st.pop();
```

## Good interview follow-up question
“What changes if we need an O(1) min-stack (track minimum)?”

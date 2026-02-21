# Operation Choice Scenarios (Interview Drills)

Use this sheet to practice selecting the right data structure from operation patterns.

## How to use
For each scenario:
1. Pick a primary structure.
2. Explain why in one sentence.
3. Mention one tradeoff.

---

## 1) Need fast append + random index access
**Best fit:** Dynamic array (`std::vector` / resizing array)
- Why: O(1) index access and amortized O(1) append.
- Tradeoff: middle insert/erase is O(n).

## 2) Need frequent insert/remove at front only
**Best fit:** Singly linked list or deque
- Why: front operations are O(1).
- Tradeoff: random access is poor (O(n)).

## 3) Need fast insert/remove at both ends
**Best fit:** Doubly linked list or deque
- Why: both ends can be O(1).
- Tradeoff: extra pointer/memory overhead.

## 4) Need LIFO behavior (undo stack, DFS)
**Best fit:** Stack
- Why: push/pop/top are O(1).
- Tradeoff: only top element is directly accessible.

## 5) Need FIFO behavior (task queue, BFS)
**Best fit:** Queue
- Why: enqueue/dequeue/front are O(1).
- Tradeoff: no random indexing.

## 6) Need key->value lookup, order not required
**Best fit:** Hash map
- Why: average O(1) insert/find/erase.
- Tradeoff: worst-case O(n), non-deterministic ordering.

## 7) Need key->value lookup with sorted iteration
**Best fit:** Balanced BST map (`std::map` style)
- Why: O(log n) operations + ordered traversal.
- Tradeoff: slower constants than hash map.

## 8) Need repeatedly smallest/largest element
**Best fit:** Heap / priority queue
- Why: top O(1), push/pop O(log n).
- Tradeoff: arbitrary search is O(n).

## 9) Need prefix search/autocomplete
**Best fit:** Trie
- Why: operations scale with key length k, O(k).
- Tradeoff: memory overhead can be high.

## 10) Need dynamic connectivity queries (are A and B connected?)
**Best fit:** Union-Find (Disjoint Set)
- Why: near-constant amortized union/find.
- Tradeoff: poor for path reconstruction/details.

## 11) Need graph traversal on sparse graph
**Best fit:** Adjacency list
- Why: BFS/DFS O(V+E) and memory proportional to edges.
- Tradeoff: edge existence check can be slower.

## 12) Need constant-time edge existence checks in dense graph
**Best fit:** Adjacency matrix
- Why: edge check O(1).
- Tradeoff: O(V^2) space.

## 13) Need to maintain sorted sequence with many middle inserts
**Best fit:** Balanced BST / skip list style structure
- Why: insert/search/remove O(log n).
- Tradeoff: more complex than vector.

## 14) Need mostly reads and very few writes, contiguous memory helpful
**Best fit:** Sorted dynamic array
- Why: binary search O(log n), excellent cache locality.
- Tradeoff: insertion/removal O(n).

## 15) Need fixed-size 2D image-like buffer
**Best fit:** Contiguous array (`vector<T>` or `unique_ptr<T[]>` with row-major indexing)
- Why: compact and cache-friendly.
- Tradeoff: manual index math (`r * cols + c`).

## 16) Need jagged rows (each row different length)
**Best fit:** Vector of vectors or pointer-to-pointer style layout
- Why: each row can vary independently.
- Tradeoff: reduced locality vs one contiguous block.

## 17) Need O(1) average membership test for large set
**Best fit:** Hash set
- Why: average O(1) contains/insert.
- Tradeoff: no ordering and collision sensitivity.

## 18) Need predecessor/successor queries
**Best fit:** Balanced BST
- Why: ordering enables lower_bound/upper_bound style queries.
- Tradeoff: O(log n) vs average O(1) hash lookups.

## 19) Need stable references/iterators while growing
**Best fit:** Linked list (node-based), sometimes tree-based containers
- Why: growth usually does not relocate existing nodes.
- Tradeoff: poorer locality and higher pointer overhead.

## 20) Need best practical default for general dynamic sequence
**Best fit:** `std::vector`
- Why: simple API, strong performance in practice, locality-friendly.
- Tradeoff: expensive middle/front insert/erase.

---

## Rapid interview framing template
When asked “Which structure should we choose?”, answer in this order:
1. **Operation profile:** reads/writes/search/order/range queries.
2. **Complexity target:** average vs worst-case requirements.
3. **Memory/layout concerns:** contiguous vs node-based.
4. **Final choice + tradeoff:** clear recommendation with one downside.

That structure sounds senior and avoids vague answers.

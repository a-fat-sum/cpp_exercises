# Common Data Structure Operations and Big-O

A quick review sheet for interview prep. Complexities shown are typical/expected unless noted.

## Legend
- n = number of elements
- h = tree height
- V = vertices, E = edges

## Dynamic Array (e.g., vector / resizing array)
| Operation | Time |
|---|---|
| Access by index | O(1) |
| Update by index | O(1) |
| Append (amortized) | O(1) |
| Append (resize step) | O(n) |
| Insert at middle/front | O(n) |
| Erase at middle/front | O(n) |
| Search unsorted | O(n) |

## Singly Linked List
| Operation | Time |
|---|---|
| Access by index | O(n) |
| Search | O(n) |
| Insert at front | O(1) |
| Insert at back (with tail) | O(1) |
| Insert at back (no tail) | O(n) |
| Delete at front | O(1) |
| Delete after known node | O(1) |

## Doubly Linked List
| Operation | Time |
|---|---|
| Access by index | O(n) |
| Search | O(n) |
| Insert at front/back | O(1) |
| Delete at front/back | O(1) |
| Delete known node | O(1) |

## Stack (LIFO)
| Operation | Time |
|---|---|
| Push | O(1) (amortized if array-backed) |
| Pop | O(1) |
| Top/Peek | O(1) |
| Search | O(n) |

## Queue (FIFO)
| Operation | Time |
|---|---|
| Enqueue | O(1) |
| Dequeue | O(1) |
| Front/Peek | O(1) |
| Search | O(n) |

## Hash Map / Hash Table
| Operation | Average | Worst |
|---|---|---|
| Insert | O(1) | O(n) |
| Lookup | O(1) | O(n) |
| Erase | O(1) | O(n) |

Notes:
- Worst case occurs with heavy collisions.
- Good hash functions + resizing keep average near O(1).

## Binary Search Tree (Unbalanced)
| Operation | Average | Worst |
|---|---|---|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |

## Balanced BST (AVL / Red-Black)
| Operation | Time |
|---|---|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |

## Binary Heap (Min/Max Heap)
| Operation | Time |
|---|---|
| Top (min/max) | O(1) |
| Insert (push) | O(log n) |
| Remove top (pop) | O(log n) |
| Build heap from array | O(n) |
| Search arbitrary value | O(n) |

## Trie (Prefix Tree)
Let k be key length.

| Operation | Time |
|---|---|
| Insert key | O(k) |
| Search key | O(k) |
| Prefix query | O(k) |

## Graph (Common Representations)

### Adjacency List
| Operation | Time |
|---|---|
| Add vertex | O(1) |
| Add edge | O(1) |
| Check edge (u,v) | O(deg(u)) |
| BFS / DFS traversal | O(V + E) |

### Adjacency Matrix
| Operation | Time |
|---|---|
| Add edge | O(1) |
| Check edge (u,v) | O(1) |
| Iterate neighbors of u | O(V) |
| BFS / DFS traversal | O(V^2) |

## Union-Find (Disjoint Set, with path compression + union by rank)
| Operation | Amortized |
|---|---|
| Find | O(alpha(n)) |
| Union | O(alpha(n)) |

Where alpha(n) is inverse Ackermann (effectively constant in practice).

## Common interview reminders
- Amortized O(1) is not the same as worst-case O(1).
- Hash tables are average-case stars; trees guarantee order.
- Choose by operation profile: access, insertion pattern, ordering needs, memory layout.
- Big-O ignores constants; cache behavior can dominate real performance.

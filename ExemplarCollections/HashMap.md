# HashMap (Separate Chaining)

## What it is
An associative container mapping keys to values using hash buckets. This implementation uses separate chaining (each bucket stores multiple entries).

## When to use
- Fast average key lookup/update/erase.
- Key order does not matter.
- You need dictionary-like semantics.

## Core complexity (average)
- Insert: **O(1)** average
- Lookup: **O(1)** average
- Erase: **O(1)** average
- Worst case for all above: **O(n)** if many collisions

## Interview talking points
- Explain hash function -> bucket index mapping.
- Explain collisions and why chaining handles them.
- Explain load factor and why rehashing is needed.

## Modern C++ features shown
- Generic key/value/hash templates.
- `std::optional` for lookup that may fail.
- Move-aware insert/update pathways.

## Common pitfalls
- Poor hash function causing heavy collisions.
- Forgetting to rehash, causing long bucket chains.
- Assuming deterministic iteration order.

## Minimal usage
```cpp
#include "HashMap.h"

exemplar::HashMap<std::string, int> freq;
freq.insert_or_assign("apple", 2);
freq["banana"] = 3;
auto maybe = freq.get("apple");
```

## Good interview follow-up question
“How does open addressing differ from separate chaining in memory and probe behavior?”

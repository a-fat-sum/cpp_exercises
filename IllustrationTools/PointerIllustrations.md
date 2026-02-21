# Pointer Illustrations: `int**`, `T[][]`, and `std::unique_ptr<T[]>`

This guide is intentionally beginner-friendly and mirrors the program in `PointerIllustrations.cpp`.

---

## 1) Double pointer with matrices (`int**`)

### Mental model
- `int** matrix` means:
  - `matrix` points to an array of row pointers (`int*`)
  - each row pointer points to an array of `int`

So with `rows=3`, `cols=4`:
1. Allocate `int*[3]`
2. For each row `r`, allocate `int[4]`

### Why this is confusing
You have *two levels* of ownership and cleanup.

### Correct delete order
```cpp
for (size_t r = 0; r < rows; ++r) {
    delete[] matrix[r];
}
delete[] matrix;
```

### Interview note
- This is flexible (rows can have different lengths).
- But memory is usually **non-contiguous**, so cache behavior is often worse.

---

## 2) Contiguous 2D block (recommended for image-like data)

Use one allocation of `rows * cols` elements.

```cpp
auto data = std::make_unique<int[]>(rows * cols);
int value = data[r * cols + c];
```

### Why this is usually better
- One allocation
- Easier ownership
- Better cache locality
- Great fit for images/buffers

### Interview note
If interviewer asks “how do you store an image?”, contiguous often wins.

---

## 3) Built-in multi-dimensional arrays (`T[][]`)

Example:
```cpp
int grid[3][4];
```

- The second dimension (`4`) is part of the type.
- Memory is contiguous row-major.
- You can range-for rows and values naturally.

### Function parameter gotcha
This compiles:
```cpp
void f(int (&arr)[3][4]);
```

But this does **not** mean “any 2D array size”. Dimensions are baked into type.

### Interview note
Common question: “Why must most dimensions be known at compile time for raw `T[][]` parameters?”

---

## 4) `std::unique_ptr<T[]>` with arrays

### What it gives you
- Automatic `delete[]`
- Exclusive ownership
- Move-only semantics

```cpp
auto arr = std::make_unique<int[]>(n);
arr[i] = 42;
```

### Key differences vs `std::unique_ptr<T>`
- `unique_ptr<T[]>` supports `operator[]`
- You should not use `*arr` like single-object pointer style

### Ownership move
```cpp
std::unique_ptr<int[]> b = std::move(arr);
// arr becomes null
```

### Interview note
Great for low-level array ownership when `std::vector<T>` is not desired.

---

## 5) How this maps to image processing

Given image `width x height` (grayscale):
- allocate `width * height`
- pixel `(x, y)` index is:

`index = y * width + x`

This is exactly what the program demonstrates.

---

## 6) Quick comparison table

| Representation | Layout | Ownership complexity | Typical use |
|---|---|---|---|
| `int**` rows | Often non-contiguous | High (multiple allocations) | Jagged rows, legacy APIs |
| `int grid[R][C]` | Contiguous | Low, static size | Fixed-size compile-time data |
| `unique_ptr<T[]>` + indexing | Contiguous | Medium, explicit indexing | Dynamic contiguous buffers/images |
| `std::vector<T>` + indexing | Contiguous | Lowest | Preferred in most modern code |

---

## 7) Practical interview answers to memorize

1. **Q: Why avoid `int**` for images?**
   - More allocations, harder cleanup, weaker locality.

2. **Q: What is row-major indexing formula?**
   - `index = row * num_cols + col`.

3. **Q: When use `unique_ptr<T[]>` over `vector<T>`?**
   - When you need explicit low-level ownership semantics and simple raw-array interop.

4. **Q: Biggest pitfall with raw 2D dynamic allocation?**
   - Incorrect delete order / leaks.

---

## 8) How to study this effectively

1. Run `PointerIllustrations` and read output section by section.
2. Put breakpoints where memory is allocated and freed.
3. In debugger, inspect pointer values (`matrix`, `matrix[r]`, `data.get()`).
4. Rewrite one section using `std::vector<int>` to compare clarity.

You’ll quickly build intuition once you watch addresses and indexing in the debugger.

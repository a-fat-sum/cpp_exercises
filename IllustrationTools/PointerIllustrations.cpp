#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

namespace {

void print_divider(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

void section_double_pointer_non_contiguous() {
    print_divider("1) Double pointer (int**) for a matrix (non-contiguous rows)");

    const std::size_t rows = 3;
    const std::size_t cols = 4;

    // Step 1: allocate an array of row pointers.
    int** matrix = new int*[rows];

    // Step 2: allocate each row independently.
    for (std::size_t r = 0; r < rows; ++r) {
        matrix[r] = new int[cols];
    }

    // Fill with sample values.
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
            matrix[r][c] = static_cast<int>(r * 10 + c);
        }
    }

    std::cout << "matrix address (int**): " << matrix << "\n";
    for (std::size_t r = 0; r < rows; ++r) {
        std::cout << "row " << r << " pointer: " << matrix[r] << " values: ";
        for (std::size_t c = 0; c < cols; ++c) {
            std::cout << std::setw(3) << matrix[r][c] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nNotice rows may be far apart in memory (not guaranteed contiguous as one big block).\n";

    // Correct cleanup: each row first, then the row-pointer array.
    for (std::size_t r = 0; r < rows; ++r) {
        delete[] matrix[r];
    }
    delete[] matrix;
}

void section_contiguous_2d_with_indexing() {
    print_divider("2) Contiguous 2D data using one block (great for images)");

    const std::size_t rows = 3;
    const std::size_t cols = 4;

    // One contiguous block of rows*cols integers.
    auto data = std::make_unique<int[]>(rows * cols);

    // Convert (r, c) -> 1D index: r * cols + c
    for (std::size_t r = 0; r < rows; ++r) {
        for (std::size_t c = 0; c < cols; ++c) {
            data[r * cols + c] = static_cast<int>(100 + r * 10 + c);
        }
    }

    std::cout << "base address: " << data.get() << "\n";
    for (std::size_t r = 0; r < rows; ++r) {
        std::cout << "row " << r << ": ";
        for (std::size_t c = 0; c < cols; ++c) {
            std::cout << std::setw(4) << data[r * cols + c] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nThis layout is cache-friendly and common in image processing.\n";
}

void section_t_multidimensional_array() {
    print_divider("3) Built-in multi-dimensional arrays: T[][]");

    // Here the second dimension (4) is part of the type.
    int grid[3][4]{};

    for (std::size_t r = 0; r < 3; ++r) {
        for (std::size_t c = 0; c < 4; ++c) {
            grid[r][c] = static_cast<int>(200 + r * 10 + c);
        }
    }

    std::cout << "grid base address: " << static_cast<void*>(grid) << "\n";
    std::cout << "&grid[0][0]: " << &grid[0][0] << "\n";
    std::cout << "&grid[1][0]: " << &grid[1][0] << " (next row, contiguous)\n\n";

    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << std::setw(4) << value;
        }
        std::cout << '\n';
    }

    std::cout << "\nWhen passing to a function, dimensions matter in the type.\n";
}

void print_fixed_cols(const int (&arr)[3][4]) {
    std::cout << "Function print_fixed_cols received int (&)[3][4]:\n";
    for (const auto& row : arr) {
        for (int value : row) {
            std::cout << std::setw(4) << value;
        }
        std::cout << '\n';
    }
}

void section_unique_ptr_array_basics() {
    print_divider("4) std::unique_ptr<T[]> basics");

    // unique_ptr<T[]> automatically calls delete[] when it goes out of scope.
    auto values = std::make_unique<int[]>(5);

    for (std::size_t i = 0; i < 5; ++i) {
        values[i] = static_cast<int>(i * i);
    }

    std::cout << "values stored with unique ownership: ";
    for (std::size_t i = 0; i < 5; ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << "\n";

    // Move ownership to another smart pointer.
    std::unique_ptr<int[]> moved = std::move(values);

    std::cout << "after move, values is " << (values ? "non-null" : "null") << '\n';
    std::cout << "moved[3] = " << moved[3] << "\n";
}

void section_image_example() {
    print_divider("5) Mini image example (grayscale)");

    const std::size_t width = 6;
    const std::size_t height = 4;

    // 1 byte per pixel grayscale image.
    auto pixels = std::make_unique<unsigned char[]>(width * height);

    // Fill with a simple gradient.
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            pixels[y * width + x] = static_cast<unsigned char>(x * 30 + y * 10);
        }
    }

    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            std::cout << std::setw(4) << static_cast<int>(pixels[y * width + x]);
        }
        std::cout << '\n';
    }

    std::cout << "\nPixel (x=2, y=1) index is y*width+x = " << (1 * width + 2)
              << ", value = " << static_cast<int>(pixels[1 * width + 2]) << '\n';
}

} // namespace

int main() {
    std::cout << "Pointer & Array Illustrations\n";

    section_double_pointer_non_contiguous();
    section_contiguous_2d_with_indexing();
    section_t_multidimensional_array();

    int demo[3][4]{};
    for (std::size_t r = 0; r < 3; ++r) {
        for (std::size_t c = 0; c < 4; ++c) {
            demo[r][c] = static_cast<int>(300 + r * 10 + c);
        }
    }
    print_fixed_cols(demo);

    section_unique_ptr_array_basics();
    section_image_example();

    std::cout << "\nDone. Re-run and step through with a debugger to inspect addresses/pointers.\n";
    return 0;
}

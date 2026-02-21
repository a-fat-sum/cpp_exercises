#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace exemplar {

// A tiny vector-like container used for interview learning.
// It demonstrates:
// - manual dynamic storage management
// - move-aware growth
// - amortized O(1) push_back
//
// This class intentionally keeps the API compact and readable.
template <typename T>
class ResizingArray {
public:
    ResizingArray() = default;

    explicit ResizingArray(std::size_t initial_capacity)
        : data_(initial_capacity ? std::make_unique<T[]>(initial_capacity) : nullptr),
          size_(0),
          capacity_(initial_capacity) {}

    // Rule-of-5 for a resource-owning type.
    ResizingArray(const ResizingArray& other)
        : data_(other.capacity_ ? std::make_unique<T[]>(other.capacity_) : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ResizingArray& operator=(const ResizingArray& other) {
        if (this == &other) {
            return *this;
        }

        ResizingArray copy(other);
        swap(copy);
        return *this;
    }

    ResizingArray(ResizingArray&&) noexcept = default;
    ResizingArray& operator=(ResizingArray&&) noexcept = default;
    ~ResizingArray() = default;

    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

    T& operator[](std::size_t index) noexcept { return data_[index]; }
    const T& operator[](std::size_t index) const noexcept { return data_[index]; }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("ResizingArray::at index out of range");
        }
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("ResizingArray::at index out of range");
        }
        return data_[index];
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("ResizingArray::front on empty container");
        }
        return data_[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("ResizingArray::front on empty container");
        }
        return data_[0];
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("ResizingArray::back on empty container");
        }
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("ResizingArray::back on empty container");
        }
        return data_[size_ - 1];
    }

    void push_back(const T& value) {
        ensure_capacity_for_one_more();
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        ensure_capacity_for_one_more();
        data_[size_++] = std::move(value);
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        ensure_capacity_for_one_more();
        data_[size_] = T(std::forward<Args>(args)...);
        return data_[size_++];
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("ResizingArray::pop_back on empty container");
        }
        --size_;
    }

    void clear() noexcept { size_ = 0; }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        auto new_data = std::make_unique<T[]>(new_capacity);
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }

    void swap(ResizingArray& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    void ensure_capacity_for_one_more() {
        if (size_ < capacity_) {
            return;
        }

        const std::size_t new_capacity = capacity_ == 0 ? 4 : capacity_ * 2;
        reserve(new_capacity);
    }

    std::unique_ptr<T[]> data_{};
    std::size_t size_{0};
    std::size_t capacity_{0};
};

template <typename T>
void swap(ResizingArray<T>& left, ResizingArray<T>& right) noexcept {
    left.swap(right);
}

} // namespace exemplar

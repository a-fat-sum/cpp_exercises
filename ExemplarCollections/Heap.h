#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace exemplar {

// A minimal binary heap (array-backed complete binary tree).
// By default with std::less<T>, this behaves as a min-heap:
// smaller values have higher priority.
template <typename T, typename Compare = std::less<T>>
class Heap {
public:
    Heap() = default;

    [[nodiscard]] bool empty() const noexcept { return data_.empty(); }
    [[nodiscard]] std::size_t size() const noexcept { return data_.size(); }

    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Heap::top on empty heap");
        }
        return data_.front();
    }

    void push(const T& value) {
        data_.push_back(value);
        sift_up(data_.size() - 1);
    }

    void push(T&& value) {
        data_.push_back(std::move(value));
        sift_up(data_.size() - 1);
    }

    template <typename... Args>
    T& emplace(Args&&... args) {
        data_.emplace_back(std::forward<Args>(args)...);
        sift_up(data_.size() - 1);
        return data_.back();
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Heap::pop on empty heap");
        }

        std::swap(data_.front(), data_.back());
        data_.pop_back();

        if (!empty()) {
            sift_down(0);
        }
    }

    void clear() noexcept { data_.clear(); }

private:
    void sift_up(std::size_t child_index) {
        while (child_index > 0) {
            const std::size_t parent_index = (child_index - 1) / 2;

            if (!compare_(data_[child_index], data_[parent_index])) {
                break;
            }

            std::swap(data_[child_index], data_[parent_index]);
            child_index = parent_index;
        }
    }

    void sift_down(std::size_t parent_index) {
        const std::size_t n = data_.size();

        while (true) {
            const std::size_t left = 2 * parent_index + 1;
            const std::size_t right = 2 * parent_index + 2;
            std::size_t best = parent_index;

            if (left < n && compare_(data_[left], data_[best])) {
                best = left;
            }

            if (right < n && compare_(data_[right], data_[best])) {
                best = right;
            }

            if (best == parent_index) {
                return;
            }

            std::swap(data_[parent_index], data_[best]);
            parent_index = best;
        }
    }

    std::vector<T> data_{};
    Compare compare_{};
};

} // namespace exemplar

#pragma once

#include "ResizingArray.h"

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace exemplar {

// A simple LIFO stack that composes ResizingArray.
// This shows a nice interview point: prefer composition over inheritance.
template <typename T>
class Stack {
public:
    Stack() = default;

    [[nodiscard]] bool empty() const noexcept { return items_.empty(); }
    [[nodiscard]] std::size_t size() const noexcept { return items_.size(); }

    void push(const T& value) { items_.push_back(value); }
    void push(T&& value) { items_.push_back(std::move(value)); }

    template <typename... Args>
    T& emplace(Args&&... args) {
        return items_.emplace_back(std::forward<Args>(args)...);
    }

    void pop() {
        if (items_.empty()) {
            throw std::runtime_error("Stack::pop on empty stack");
        }
        items_.pop_back();
    }

    T& top() {
        if (items_.empty()) {
            throw std::runtime_error("Stack::top on empty stack");
        }
        return items_.back();
    }

    const T& top() const {
        if (items_.empty()) {
            throw std::runtime_error("Stack::top on empty stack");
        }
        return items_.back();
    }

    void clear() noexcept { items_.clear(); }

private:
    ResizingArray<T> items_{};
};

} // namespace exemplar

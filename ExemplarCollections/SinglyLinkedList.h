#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

namespace exemplar {

// A minimal singly linked list.
// Node ownership uses std::unique_ptr so destruction is automatic.
template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;

    SinglyLinkedList(const SinglyLinkedList& other) {
        const Node* cursor = other.head_.get();
        while (cursor != nullptr) {
            push_back(cursor->value);
            cursor = cursor->next.get();
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        SinglyLinkedList copy(other);
        swap(copy);
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&&) noexcept = default;
    SinglyLinkedList& operator=(SinglyLinkedList&&) noexcept = default;
    ~SinglyLinkedList() = default;

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    void push_front(const T& value) {
        auto new_head = std::make_unique<Node>(value);
        if (empty()) {
            tail_ = new_head.get();
        }

        new_head->next = std::move(head_);
        head_ = std::move(new_head);
        ++size_;
    }

    void push_front(T&& value) {
        auto new_head = std::make_unique<Node>(std::move(value));
        if (empty()) {
            tail_ = new_head.get();
        }

        new_head->next = std::move(head_);
        head_ = std::move(new_head);
        ++size_;
    }

    void push_back(const T& value) {
        auto node = std::make_unique<Node>(value);
        append_node(std::move(node));
    }

    void push_back(T&& value) {
        auto node = std::make_unique<Node>(std::move(value));
        append_node(std::move(node));
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("SinglyLinkedList::pop_front on empty list");
        }

        head_ = std::move(head_->next);
        --size_;

        if (size_ == 0) {
            tail_ = nullptr;
        }
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("SinglyLinkedList::front on empty list");
        }
        return head_->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("SinglyLinkedList::front on empty list");
        }
        return head_->value;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("SinglyLinkedList::back on empty list");
        }
        return tail_->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("SinglyLinkedList::back on empty list");
        }
        return tail_->value;
    }

    [[nodiscard]] bool contains(const T& target) const {
        const Node* cursor = head_.get();
        while (cursor != nullptr) {
            if (cursor->value == target) {
                return true;
            }
            cursor = cursor->next.get();
        }
        return false;
    }

    std::optional<T> find_first(const T& target) const {
        const Node* cursor = head_.get();
        while (cursor != nullptr) {
            if (cursor->value == target) {
                return cursor->value;
            }
            cursor = cursor->next.get();
        }
        return std::nullopt;
    }

    void clear() noexcept {
        head_.reset();
        tail_ = nullptr;
        size_ = 0;
    }

    void swap(SinglyLinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}

        T value;
        std::unique_ptr<Node> next{};
    };

    void append_node(std::unique_ptr<Node> node) {
        Node* raw = node.get();
        if (empty()) {
            head_ = std::move(node);
            tail_ = raw;
        } else {
            tail_->next = std::move(node);
            tail_ = raw;
        }
        ++size_;
    }

    std::unique_ptr<Node> head_{};
    Node* tail_{nullptr};
    std::size_t size_{0};
};

template <typename T>
void swap(SinglyLinkedList<T>& left, SinglyLinkedList<T>& right) noexcept {
    left.swap(right);
}

} // namespace exemplar

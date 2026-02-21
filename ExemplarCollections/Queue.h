#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace exemplar {

// A FIFO queue implemented with a singly linked chain.
// Enqueue at tail, dequeue at head: both O(1).
template <typename T>
class Queue {
public:
    Queue() = default;

    Queue(const Queue& other) {
        for (Node* cursor = other.head_; cursor != nullptr; cursor = cursor->next) {
            enqueue(cursor->value);
        }
    }

    Queue& operator=(const Queue& other) {
        if (this == &other) {
            return *this;
        }

        Queue copy(other);
        swap(copy);
        return *this;
    }

    Queue(Queue&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;

        return *this;
    }

    ~Queue() { clear(); }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    void enqueue(const T& value) { link_back(new Node(value)); }
    void enqueue(T&& value) { link_back(new Node(std::move(value))); }

    void dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue::dequeue on empty queue");
        }

        Node* old_head = head_;
        head_ = head_->next;
        delete old_head;
        --size_;

        if (size_ == 0) {
            tail_ = nullptr;
        }
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("Queue::front on empty queue");
        }
        return head_->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue::front on empty queue");
        }
        return head_->value;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("Queue::back on empty queue");
        }
        return tail_->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue::back on empty queue");
        }
        return tail_->value;
    }

    void clear() noexcept {
        Node* cursor = head_;
        while (cursor != nullptr) {
            Node* next = cursor->next;
            delete cursor;
            cursor = next;
        }

        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    void swap(Queue& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}

        T value;
        Node* next{nullptr};
    };

    void link_back(Node* node) {
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }

        ++size_;
    }

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};
};

template <typename T>
void swap(Queue<T>& left, Queue<T>& right) noexcept {
    left.swap(right);
}

} // namespace exemplar

#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace exemplar {

// A minimal doubly linked list with head/tail pointers.
// We use raw pointers for educational visibility of node linkage.
// Resource cleanup is centralized in clear()/destructor.
template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList() = default;

    DoublyLinkedList(const DoublyLinkedList& other) {
        for (Node* cursor = other.head_; cursor != nullptr; cursor = cursor->next) {
            push_back(cursor->value);
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this;
        }

        DoublyLinkedList copy(other);
        swap(copy);
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
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

    ~DoublyLinkedList() { clear(); }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    void push_front(const T& value) { link_front(new Node(value)); }
    void push_front(T&& value) { link_front(new Node(std::move(value))); }
    void push_back(const T& value) { link_back(new Node(value)); }
    void push_back(T&& value) { link_back(new Node(std::move(value))); }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::pop_front on empty list");
        }

        Node* old_head = head_;
        head_ = head_->next;

        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete old_head;
        --size_;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::pop_back on empty list");
        }

        Node* old_tail = tail_;
        tail_ = tail_->prev;

        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete old_tail;
        --size_;
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::front on empty list");
        }
        return head_->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::front on empty list");
        }
        return head_->value;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::back on empty list");
        }
        return tail_->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("DoublyLinkedList::back on empty list");
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

    void swap(DoublyLinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}

        T value;
        Node* prev{nullptr};
        Node* next{nullptr};
    };

    void link_front(Node* node) {
        node->next = head_;
        if (head_ != nullptr) {
            head_->prev = node;
        } else {
            tail_ = node;
        }

        head_ = node;
        ++size_;
    }

    void link_back(Node* node) {
        node->prev = tail_;
        if (tail_ != nullptr) {
            tail_->next = node;
        } else {
            head_ = node;
        }

        tail_ = node;
        ++size_;
    }

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};
};

template <typename T>
void swap(DoublyLinkedList<T>& left, DoublyLinkedList<T>& right) noexcept {
    left.swap(right);
}

} // namespace exemplar

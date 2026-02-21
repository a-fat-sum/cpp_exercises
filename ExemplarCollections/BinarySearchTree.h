#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace exemplar {

// Minimal Binary Search Tree (BST).
// Default ordering uses std::less<T>.
// This implementation is intentionally not self-balancing.
template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree& other) : root_(clone(other.root_)), size_(other.size_), compare_(other.compare_) {}

    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this;
        }

        BinarySearchTree copy(other);
        swap(copy);
        return *this;
    }

    BinarySearchTree(BinarySearchTree&&) noexcept = default;
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept = default;
    ~BinarySearchTree() = default;

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    // Inserts if key does not already exist.
    // Returns true if inserted, false if key already present.
    bool insert(const T& value) { return insert_impl(root_, value); }
    bool insert(T&& value) { return insert_impl(root_, std::move(value)); }

    [[nodiscard]] bool contains(const T& value) const {
        Node* cursor = root_.get();
        while (cursor != nullptr) {
            if (compare_(value, cursor->value)) {
                cursor = cursor->left.get();
            } else if (compare_(cursor->value, value)) {
                cursor = cursor->right.get();
            } else {
                return true;
            }
        }
        return false;
    }

    // Erase by key. Returns true if element was found and removed.
    bool erase(const T& value) { return erase_impl(root_, value); }

    [[nodiscard]] std::optional<T> min_value() const {
        if (empty()) {
            return std::nullopt;
        }

        Node* cursor = root_.get();
        while (cursor->left) {
            cursor = cursor->left.get();
        }
        return cursor->value;
    }

    [[nodiscard]] std::optional<T> max_value() const {
        if (empty()) {
            return std::nullopt;
        }

        Node* cursor = root_.get();
        while (cursor->right) {
            cursor = cursor->right.get();
        }
        return cursor->value;
    }

    // In-order traversal yields sorted order in a BST.
    [[nodiscard]] std::vector<T> in_order() const {
        std::vector<T> out;
        out.reserve(size_);
        in_order_impl(root_.get(), out);
        return out;
    }

    void clear() noexcept {
        root_.reset();
        size_ = 0;
    }

    void swap(BinarySearchTree& other) noexcept {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
        std::swap(compare_, other.compare_);
    }

private:
    struct Node {
        explicit Node(const T& v) : value(v) {}
        explicit Node(T&& v) : value(std::move(v)) {}

        T value;
        std::unique_ptr<Node> left{};
        std::unique_ptr<Node> right{};
    };

    template <typename U>
    bool insert_impl(std::unique_ptr<Node>& current, U&& value) {
        if (!current) {
            current = std::make_unique<Node>(std::forward<U>(value));
            ++size_;
            return true;
        }

        if (compare_(value, current->value)) {
            return insert_impl(current->left, std::forward<U>(value));
        }

        if (compare_(current->value, value)) {
            return insert_impl(current->right, std::forward<U>(value));
        }

        return false;
    }

    bool erase_impl(std::unique_ptr<Node>& current, const T& value) {
        if (!current) {
            return false;
        }

        if (compare_(value, current->value)) {
            return erase_impl(current->left, value);
        }

        if (compare_(current->value, value)) {
            return erase_impl(current->right, value);
        }

        // Found node to delete.
        if (!current->left) {
            current = std::move(current->right);
            --size_;
            return true;
        }

        if (!current->right) {
            current = std::move(current->left);
            --size_;
            return true;
        }

        // Two children:
        // 1) find smallest node in right subtree (in-order successor)
        // 2) copy successor value into current
        // 3) delete successor node recursively
        Node* successor = current->right.get();
        while (successor->left) {
            successor = successor->left.get();
        }

        current->value = successor->value;
        return erase_impl(current->right, successor->value);
    }

    static std::unique_ptr<Node> clone(const std::unique_ptr<Node>& node) {
        if (!node) {
            return nullptr;
        }

        auto new_node = std::make_unique<Node>(node->value);
        new_node->left = clone(node->left);
        new_node->right = clone(node->right);
        return new_node;
    }

    static void in_order_impl(const Node* node, std::vector<T>& out) {
        if (!node) {
            return;
        }

        in_order_impl(node->left.get(), out);
        out.push_back(node->value);
        in_order_impl(node->right.get(), out);
    }

    std::unique_ptr<Node> root_{};
    std::size_t size_{0};
    Compare compare_{};
};

template <typename T, typename Compare>
void swap(BinarySearchTree<T, Compare>& left, BinarySearchTree<T, Compare>& right) noexcept {
    left.swap(right);
}

} // namespace exemplar

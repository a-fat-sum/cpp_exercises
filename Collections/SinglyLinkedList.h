#pragma once

#include <memory>

namespace collections
{
    template <typename T>
    class SinglyLinkedList 
    {
    public:
        SinglyLinkedList() = default;

        void push_front(const T& value);
        void push_back(const T& value);
        void push_back_with_tail(const T& value);

        T& front();
        T& back();
        void pop_front();
        
        void print() const;

    private:
        struct Node
        {
            T value;
            std::unique_ptr<Node> next;

            Node(const T& value_);
        };

        std::unique_ptr<Node> m_head = nullptr;
        Node* m_tail = nullptr;
        size_t m_size = 0;
    };
}

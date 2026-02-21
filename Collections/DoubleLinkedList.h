#pragma once

namespace collections
{
    template <typename T>
    class DoubleLinkedList
    {
    public:
        DoubleLinkedList() = default;
        ~DoubleLinkedList();

        void push_front(const T& value);
        void push_back(const T& value);

        void pop_front();
        void pop_back();

        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;

        [[nodiscard]] T& front();
        [[nodiscard]] T& back();

        void print() const;

    private:
        struct Node
        {
            T value;
            Node* prev = nullptr;
            Node* next = nullptr;

            Node(const T& value);
        };
        
        void clear();

        Node* m_head = nullptr;
        Node* m_tail = nullptr;
        size_t m_size = 0;
    };
}

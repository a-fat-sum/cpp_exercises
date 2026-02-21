#include "SinglyLinkedList.h"

#include <iostream>
#include <string>
#include <stdexcept>

namespace collections
{
    template <typename T>
    SinglyLinkedList<T>::Node::Node(const T& value_) : value(value_), next(nullptr) 
    {

    }

    template <typename T>
    void SinglyLinkedList<T>::push_front(const T& value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
        new_node->next = std::move(m_head);
        m_head = std::move(new_node);

        if (m_head->next == nullptr)
        {
            // Any subsequent push_front's don't change the tail
            m_tail = m_head.get();
        }

        m_size++;
    }

    template <typename T>
    void SinglyLinkedList<T>::push_back(const T& value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
        new_node->next = nullptr;
        m_size++;

        if (m_head == nullptr)
        {
            m_head = std::move(new_node);
            return;
        }

        Node* current = m_head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }

        current->next = std::move(new_node);
    }

    template <typename T>
    void SinglyLinkedList<T>::push_back_with_tail(const T& value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
        new_node->next = nullptr;

        if (m_head == nullptr)
        {
            push_front(value);
            return;
        }

        Node* current_tail = m_tail;
        m_tail = new_node.get();
        current_tail->next = std::move(new_node);
        m_size++;
    }

    template <typename T>
    T& SinglyLinkedList<T>::front()
    {
        if (m_head == nullptr)
        {
            throw std::out_of_range("front on empty list");
        }
        return m_head->value;
    }

    template <typename T>
    T& SinglyLinkedList<T>::back()
    {
        if (m_tail == nullptr)
        {
            throw std::out_of_range("back on empty list");
        }
        return m_tail->value;
    }

    template <typename T>
    void SinglyLinkedList<T>::pop_front()
    {
        if (m_head == nullptr)
        {
            return;
        }

        m_head = std::move(m_head->next);
        m_size--;
    }

    template <typename T>
    void SinglyLinkedList<T>::print() const
    {
        const Node* current = m_head.get();
        while (current != nullptr)
        {
            std::cout << current->value << " -> ";
            current = current->next.get();
        }
        std::cout << "Size = " << m_size << " " << std::endl;
    }

    template class SinglyLinkedList<int>;
    template class SinglyLinkedList<float>;
    template class SinglyLinkedList<double>;
    template class SinglyLinkedList<std::string>;
    template class SinglyLinkedList<char>;
}
#include "DoubleLinkedList.h"

#include <stdexcept>
#include <string>
#include <iostream>

namespace collections
{
    template <typename T>
    DoubleLinkedList<T>::Node::Node(const T& value_) : value(value_), prev(nullptr), next(nullptr)
    {

    }

    template <typename T>
    DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    template <typename T>
    void DoubleLinkedList<T>::clear()
    {
        Node* current = m_head;
        while (current != nullptr)
        {
            Node* prev = current;
            current = current->next;
            delete prev;
        }
        
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    template <typename T>
    size_t DoubleLinkedList<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    bool DoubleLinkedList<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    void DoubleLinkedList<T>::push_front(const T& value)
    {
        Node* new_node = new Node(value);
        new_node->next = m_head;
        new_node->prev = nullptr;
        
        if (!empty())
        {
            m_head->prev = new_node;
        }
        
        m_head = new_node;
        m_size++;

        if (size() == 1)
        {
            m_tail = m_head;
        }
    }

    template <typename T>
    void DoubleLinkedList<T>::push_back(const T& value)
    {
        if (empty())
        {
            push_front(value);
            return;
        }

        Node* new_node = new Node(value);
        new_node->prev = m_tail;
        new_node->next = nullptr;
        m_tail->next = new_node;
        m_tail = new_node;
        m_size++;
    }

    template <typename T>
    void DoubleLinkedList<T>::print() const
    {
        Node* current = m_head;
        while (current != nullptr)
        {
            std::cout << current->value;
            if (current->next != nullptr)
            {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
        std::cout << "Size = " << size() << std::endl;
    }

    template <typename T>
    T& DoubleLinkedList<T>::front()
    {
        if (empty())
        {
            throw std::out_of_range("front on empty double linked list");
        }

        return m_head->value;
    }

    template <typename T>
    T& DoubleLinkedList<T>::back()
    {
        if (empty())
        {
            throw std::out_of_range("back on empty double linked list");
        }

        return m_tail->value;
    }

    template <typename T>
    void DoubleLinkedList<T>::pop_front()
    {
        if (empty())
        {
            return;
        }

        Node* temp = m_head;
        m_head = m_head->next;

        if (m_head)
        {
            m_head->prev = nullptr;
        }
        
        delete temp;
        m_size--;

        if (size() == 1)
        {
            m_tail = m_head;
        }

        if (size() == 0)
        {
            m_tail = nullptr;
        }
    }

    template <typename T>
    void DoubleLinkedList<T>::pop_back()
    {
        if (empty())
        {
            return;
        }

        Node* temp = m_tail;
        m_tail = m_tail->prev;

        if (m_tail)
        {
            m_tail->next = nullptr;
        }
        
        delete temp;
        m_size--;

        if (size() == 1)
        {
            m_head = m_tail;
        }

        if (size() == 0)
        {
            m_head = nullptr;
        }
    }
    
    template class DoubleLinkedList<int>;
    template class DoubleLinkedList<float>;
    template class DoubleLinkedList<double>;
    template class DoubleLinkedList<char>;
    template class DoubleLinkedList<std::string>;
}
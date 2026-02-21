#include "ResizingArray.h"

#include <stdexcept>
#include <string>
#include <iostream>

namespace collections
{
    template <typename T>
    ResizingArray<T>::ResizingArray() : ResizingArray(1) {}

    template <typename T>
    ResizingArray<T>::ResizingArray(size_t initial_capacity)
    {
        m_data = std::make_unique<T[]>(initial_capacity);
        m_capacity = initial_capacity;
        m_size = 0;
    }

    template <typename T>
    void ResizingArray<T>::print() const
    {
        for (size_t i = 0; i < size(); ++i)
        {
            std::cout << m_data[i];
            if (i != size() - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << std::endl;
        std::cout << "Size = " << size() << std::endl;
    }

    template <typename T>
    void ResizingArray<T>::push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            resize(m_capacity * 2);
        }

        m_data[m_size++] = value;
    }

    template <typename T>
    void ResizingArray<T>::resize(size_t capacity)
    {
        std::cout << "Invoking resizing operation" << std::endl;
        std::unique_ptr<T[]> temp = std::make_unique<T[]>(capacity);
        for (size_t i = 0; i < size(); ++i)
        {
            temp[i] = m_data[i];
        }

        m_data = std::move(temp);
        m_capacity = capacity;
    }

    template <typename T>
    size_t ResizingArray<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    bool ResizingArray<T>::empty() const
    {
        return m_size == 0;
    }

    template <typename T>
    T& ResizingArray<T>::operator[](size_t index)
    {
        if (index >= size())
        {
            throw std::out_of_range("Accessing index out of range in ResizingArray [] operator");
        }

        return m_data[index];
    }

    template <typename T>
    const T& ResizingArray<T>::operator[](size_t index) const
    {
        if (index >= size())
        {
            throw std::out_of_range("Accessing index out of range in ResizingArray [] operator");
        }

        return m_data[index];
    }


    template class ResizingArray<int>;
    template class ResizingArray<float>;
    template class ResizingArray<double>;
    template class ResizingArray<char>;
    template class ResizingArray<std::string>;
}
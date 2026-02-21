#pragma once

#include <cstddef>
#include <memory>

namespace collections
{
    template <typename T>
    class ResizingArray
    {
    public:
        ResizingArray();
        ResizingArray(size_t initial_capacity);

        void push_back(const T& value);
        [[nodiscard]] T& operator[](size_t index);
        [[nodiscard]] const T& operator[](size_t index) const;
        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;

        void print() const;
    private:

        void resize(size_t capacity);

        std::unique_ptr<T[]> m_data;
        size_t m_size = 0;
        size_t m_capacity = 0;
    };
};

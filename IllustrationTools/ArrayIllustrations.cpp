#include "ResizingArray.h"

#include <iostream>

using namespace collections;
int main()
{
    ResizingArray<double> array;
    array.push_back(1.0);
    array.print();

    array.push_back(2.0);
    array.push_back(3.0);
    array.push_back(4.0);
    array.print();

    std::cout << "Element at index 2 = " << array[2] << std::endl;

    return 0;
}
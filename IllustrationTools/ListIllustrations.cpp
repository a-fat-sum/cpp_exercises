#include "DoubleLinkedList.h"

#include <string>
#include <iostream>

using namespace collections;
int main()
{
    DoubleLinkedList<std::string> list;

    list.push_back("cat");
    list.push_back("is");
    list.push_back("very");
    list.push_back("cute");
    list.push_front("My");
    list.print();


    std::cout << "At head of list is " << list.front() << std::endl;
    std::cout << "At back of list is " << list.back() << std::endl;

    list.pop_front();
    list.print();

    list.pop_back();
    list.print();

    return 0;
}
#include "Foo.h"
#include <iostream>

Foo::Foo(const std::string& message) : message(message) {}

void Foo::print() const {
    std::cout << "Foo says: " << message << std::endl;
}

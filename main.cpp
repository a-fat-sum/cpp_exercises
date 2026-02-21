#include "Foo.h"
#include <iostream>

int main() {
    std::cout << "Main function started." << std::endl;
    Foo myFoo("Hello from Foo!");
    myFoo.print();
    return 0;
}

#ifndef FOO_H
#define FOO_H

#include <string>

class Foo {
public:
    Foo(const std::string& message);
    void print() const;

private:
    std::string message;
};

#endif // FOO_H

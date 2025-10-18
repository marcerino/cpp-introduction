#include "myvector.hpp"
#include <cstdint>
#include <stddef.h>
#include <iostream>
int main() {
    MyVector p = MyVector<uint16_t>();
    size_t a = 8;
    size_t const size = p.size();
    std::cout << a << size <<"\n";
}
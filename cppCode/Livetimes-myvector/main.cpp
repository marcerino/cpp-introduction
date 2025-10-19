#include "myvector.hpp"
#include <cstdint>
#include <iostream>

int main() {
    MyVector<uint16_t> p{2};
    size_t a = 8;
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);
    p.push_back(7);
    size_t const size = p.size();

    a = p[4];
    std::cout << a << size << "\n";
}
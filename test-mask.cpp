#include <iostream>
#include "fixed.hpp"

int main() {
    std::cout << sizeof(long long int) << " " << sizeof(long double) << std::endl;

    for (char i = -16; i <= 16; ++i) {
        auto x = Fixed<2, 2>::mask(i);
        std::cout
                << (int) i
                << " -> " << std::bitset<8>(i)
                << " -> " << std::bitset<8>(x)
                << " -> " << (int) x
                << std::endl;
    }

    return 0;
}
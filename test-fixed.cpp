#include <iostream>
#include <cmath>
#include "fixed.hpp"

int main() {
    Fixed<3, 2> f1(1.5);
    Fixed<4, 3> f2(2.25);
    Fixed<3, 3> f3(3.125);
    Fixed<16, 2> f4(3.625);
    Fixed<32, 5> f6(f1);

    std::cout << Fixed<1, 7>(sin(0.3)) << std::endl;
    std::cout << Fixed<1, 15>(sin(0.3)) << std::endl;
    std::cout << Fixed<1, 31>(sin(0.3)) << std::endl;
    std::cout << std::endl;

    std::cout << Fixed<1, 7>(sin(M_PI / 2) - 0.00000001) << std::endl;
    std::cout << Fixed<1, 15>(sin(M_PI / 2) - 0.00000001) << std::endl;
    std::cout << Fixed<1, 31>(sin(M_PI / 2) - 0.00000001) << std::endl;
    std::cout << std::endl;

    std::cout << f4 << std::endl;
    f4 = 3.75;
    std::cout << f4 << std::endl;
    std::cout << f4++ << std::endl;
    std::cout << f4 << std::endl;
    std::cout << ++f4 << std::endl;
    std::cout << f4 << std::endl;

    std::cout << std::endl;
    std::cout << f1 << std::endl;
    std::cout << f6 << std::endl;
    std::cout << Fixed<8, 5>(f1) << std::endl;

    std::cout << std::endl;
    std::cout << f1 + 8 << std::endl;
    std::cout << f1 - 2 << std::endl;

    std::cout << std::endl;
    std::cout << f1 * 4 << std::endl;
    std::cout << f1 * 3 << std::endl;
    std::cout << f1 / 2 << std::endl;
    std::cout << f1 / 3 << std::endl;

    std::cout << std::endl;
    std::cout << f1 + f2 << std::endl;
    std::cout << f2 + f1 << std::endl;
    std::cout << f1 - f3 << std::endl;

    std::cout << std::endl;
    std::cout << f3 * f2 << std::endl;
    std::cout << f1 / f2 << std::endl;

    std::cout << std::endl;
    std::cout << f1 / f4 << std::endl;
    std::cout << f4 / f1 << std::endl;

    std::cout << std::endl;
    std::cout << Fixed<8, 0>(253) << std::endl;
    std::cout << Fixed<8, 0>(253) + 5 << std::endl;

    std::cout << std::endl;
    std::cout << Fixed<16, 30>(3.3) << std::endl;
    std::cout << Fixed<16, 30>(3.3) + Fixed<16, 30>(3.3) << std::endl;
    std::cout << Fixed<16, 30>(3.3) * 2 << std::endl;
    std::cout << Fixed<16, 30>(3.3) * 3 << std::endl;

    std::cout << std::endl;
    std::cout << Fixed<8, 0>(1374.79) << std::endl;
    std::cout << Fixed<16, 0>(1374.79) << std::endl;
    std::cout << Fixed<16, 1>(1374.79) << std::endl;
    std::cout << Fixed<16, 2>(1374.79) << std::endl;
    std::cout << Fixed<16, 3>(1374.79) << std::endl;
    std::cout << Fixed<16, 4>(1374.79) << std::endl;
    std::cout << Fixed<16, 5>(1374.79) << std::endl;
    std::cout << Fixed<16, 6>(1374.79) << std::endl;
    std::cout << Fixed<16, 7>(1374.79) << std::endl;
    std::cout << Fixed<16, 8>(1374.79) << std::endl;
    std::cout << Fixed<16, 9>(1374.79) << std::endl;

    std::cout << std::endl;
    std::cout << Fixed<16, 30>(74.79) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) >> 1) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) >> 2) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) >> 3) << std::endl;

    std::cout << std::endl;
    std::cout << Fixed<16, 30>(74.79) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) << 1) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) << 2) << std::endl;
    std::cout << (Fixed<16, 30>(74.79) << 3) << std::endl;

    return 0;
}
#include <iostream>
#include <cmath>
#include "fixed.hpp"

using namespace std;

int main() {
    Fixed<4, 4> f1(1.5);
    Fixed<4, 9> f2(2.25);
    Fixed<3, 6> f3(3.125);
    Fixed<16, 8> f4(3.625);
    Fixed<32, 5> f6(f1);

    cout << endl << "Variables:" << endl;
    cout << f1 << endl;
    cout << f2 << endl;
    cout << f3 << endl;
    cout << f4 << endl;
    cout << f6 << endl;

    cout << endl;
    f4 = 3.75;
    cout << f4 << endl;
    cout << f4++ << endl;
    cout << f4 << endl;
    cout << ++f4 << endl;
    cout << f4 << endl;

    cout << endl;
    cout << f1 << endl;
    cout << f6 << endl;
    cout << Fixed<8, 5>(f1) << endl;
    cout << Fixed<8, 64>(f1) << endl;

    cout << endl << "Sum Minus:" << endl;
    cout << f1 + f2 << endl;
    cout << f2 + f1 << endl;
    cout << f1 - f3 << endl;
    cout << endl;
    cout << f1 + 3 << endl;
    cout << f1 + 8 << endl;
    cout << f1 - 2 << endl;

    cout << endl << "Mul Div:" << endl;
    cout << f1 << endl;
    cout << f1 * 4 << endl;
    cout << f1 * 3 << endl;
    cout << f1 / 2 << endl;
    cout << f1 / 3 << endl;
    cout << endl;
    cout << f3 * f2 << endl;
    cout << f1 / f2 << endl;
    cout << endl;
    cout << f1 / f4 << endl;
    cout << f4 / f1 << endl;

    cout << endl << "Edge:" << endl;
    cout << Fixed<9, 0>(253) << endl;
    cout << Fixed<9, 0>(253) + 5 << endl;

    cout << endl << "Precision:" << endl;
    cout << Fixed<16, 30>(3.3) << endl;
    cout << Fixed<16, 30>(3.3) + Fixed<16, 30>(3.3) << endl;
    cout << Fixed<16, 30>(3.3) * 2 << endl;
    cout << Fixed<16, 30>(3.3) * 3 << endl;
    cout << endl;
    cout << Fixed<8, 0>(1374.79) << endl;
    cout << Fixed<16, 0>(1374.79) << endl;
    cout << Fixed<16, 1>(1374.79) << endl;
    cout << Fixed<16, 2>(1374.79) << endl;
    cout << Fixed<16, 3>(1374.79) << endl;
    cout << Fixed<16, 4>(1374.79) << endl;
    cout << Fixed<16, 5>(1374.79) << endl;
    cout << Fixed<16, 6>(1374.79) << endl;
    cout << Fixed<16, 7>(1374.79) << endl;
    cout << Fixed<16, 8>(1374.79) << endl;
    cout << Fixed<16, 9>(1374.79) << endl;

    cout << endl << "Shift:" << endl;
    cout << Fixed<16, 30>(74.79) << endl;
    cout << (Fixed<16, 30>(74.79) >> 1) << endl;
    cout << (Fixed<16, 30>(74.79) >> 2) << endl;
    cout << (Fixed<16, 30>(74.79) >> 3) << endl;
    cout << endl;
    cout << Fixed<16, 30>(74.79) << endl;
    cout << (Fixed<16, 30>(74.79) << 1) << endl;
    cout << (Fixed<16, 30>(74.79) << 2) << endl;
    cout << (Fixed<16, 30>(74.79) << 3) << endl;

    cout << endl << "Sin:" << endl;
    cout << Fixed<2, 7>(sin(0.3)) << endl;
    cout << Fixed<2, 15>(sin(0.3)) << endl;
    cout << Fixed<2, 25>(sin(0.3)) << endl;
    cout << Fixed<2, 30>(sin(0.3)) << endl;
    cout << Fixed<2, 31>(sin(0.3)) << endl;
    cout << Fixed<2, 32>(sin(0.3)) << endl;
    cout << Fixed<2, 40>(sin(0.3)) << endl;
    cout << endl;
    cout << Fixed<2, 7>(sin(M_PI / 2) - 0.00000001) << endl;
    cout << Fixed<2, 15>(sin(M_PI / 2) - 0.00000001) << endl;
    cout << Fixed<2, 31>(sin(M_PI / 2) - 0.00000001) << endl;
    cout << endl;

    return 0;
}
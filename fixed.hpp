#pragma once

#include <iostream>
#include <bitset>

/**
 * this Qmn fixed point simulator
 * value range is from -2^(m-1) inclusive to +2^(m-1) exclusive
 * quantize precision is 2^(-n)
 * it uses (long double) to calculate in floating-point space
 * and convert it to (long long int) which holds
 * a v*(2^n) 2's complement version of result
 * ATTENTION: Due to typing limits and how c++ templates
 * works all of +|-|*|/ return Qmn from LHS
 * which is what exactly is a fixed-point Qmn precision
 *
 * Developer: Hossain Khademian (@hkhademian)
 * LICENSE: use as long as you don't claim it's yours
 * free for small companies and small scale projects
 *
 * @tparam m number of bits used to hold integral part
 * @tparam n number of bits used to hold fractional part
 */
template<int m, int n>
class Fixed {
#define self (*this)

public:
    using INNER_T = signed long long int;

    static inline INNER_T mask(INNER_T inp) {
        const INNER_T signbit = (unsigned long long int) 1 << (m + n - 1);
        const INNER_T usable = ((unsigned long long int) 1 << (m + n)) - 1;
        return (inp & usable) | (!(inp & signbit) ? 0 : ~usable);
    }

    static inline std::bitset<n> mask_frac(INNER_T inp) {
        return inp & ((1 << n) - 1);
    }

    static inline std::bitset<m> mask_int(INNER_T inp) {
        return (inp >> n) & ((1 << m) - 1);
    }

    static Fixed fromRaw(INNER_T raw) {
        Fixed tmp;
        tmp.val = mask(raw);
        return tmp;
    }

    friend std::ostream &operator<<(std::ostream &os, const Fixed<m, n> &f) {
        return os << "Fixed[" << m << "," << n << "]("
                  << (long double) f << " ~ "
                  // << std::bitset<8 * sizeof(INNER_T)>(f.val)
                  << mask_int(f.val) << "." << mask_frac(f.val)
                  << ")";
    }

private:
    INNER_T val = 0;

public:
    Fixed() : val(0) {}

    Fixed(const Fixed &f) : val(mask(f.val)) {}

    Fixed(long long int v) : val(mask(v << n)) {} // NOLINT(google-explicit-constructor)

    Fixed(long double v) : val(mask(v * (1 << n))) {} // NOLINT(google-explicit-constructor)

    Fixed(long int v) : Fixed((long long int) v) {} // NOLINT(google-explicit-constructor)

    Fixed(int v) : Fixed((long long int) v) {} // NOLINT(google-explicit-constructor)

    Fixed(short v) : Fixed((long long int) v) {} // NOLINT(google-explicit-constructor)

    Fixed(char v) : Fixed((long long int) v) {} // NOLINT(google-explicit-constructor)

    Fixed(double v) : Fixed((long double) v) {} // NOLINT(google-explicit-constructor)

    Fixed(float v) : Fixed((long double) v) {} // NOLINT(google-explicit-constructor)

    /** cross precision conversion */
    template<int mm, int nn>
    Fixed(const Fixed<mm, nn> &f) : Fixed((long double) f) {} // NOLINT(google-explicit-constructor)

    ~Fixed() = default;

    explicit operator long double() const { return (((long long int) val) / ((long double) (1 << n))); }

    explicit operator double() const { return (long double) self; }

    explicit operator float() const { return (long double) self; }

    explicit operator long long int() const { return (long double) self; }

    explicit operator long int() const { return (long double) self; }

    explicit operator int() const { return (long double) self; }

    explicit operator short() const { return (long double) self; }

    explicit operator char() const { return (long double) self; }

    explicit operator std::bitset<n + m>() const { return mask(val); }

    long long int getRawBits() const { return val; }

    void setRawBits(long long int const raw) { val = mask(raw); }

    Fixed operator+(const Fixed &f) const { return ((long double) self + (long double) f); }

    Fixed operator-(const Fixed &f) const { return ((long double) self - (long double) f); }

    Fixed operator*(const Fixed &f) const { return ((long double) self * (long double) f); }

    Fixed operator/(const Fixed &f) const { return ((long double) self / (long double) f); }

    Fixed &operator=(const Fixed &f) { return val = mask(f.val), self; }

    Fixed &operator+=(const Fixed &f) { return val = (self + f).val, self; }

    Fixed &operator-=(const Fixed &f) { return val = (self - f).val, self; }

    Fixed &operator*=(const Fixed &f) { return val = (self * f).val, self; }

    Fixed &operator/=(const Fixed &f) { return val = (self / f).val, self; }

    Fixed &operator++() { return val = (self + 1).val, self; }

    Fixed &operator--() { return val = (self - 1).val, self; }

    Fixed operator++(int) &{ // NOLINT(cert-dcl21-cpp)
        Fixed tmp(self);
        val = (self + 1).val;
        return tmp;
    }

    Fixed operator--(int) &{ // NOLINT(cert-dcl21-cpp)
        const Fixed tmp(self);
        val = (self - 1).val;
        return tmp;
    }

    bool operator<(const Fixed &f) const { return val < f.val; }

    bool operator>(const Fixed &f) const { return val > f.val; }

    bool operator<=(const Fixed &f) const { return val <= f.val; }

    bool operator>=(const Fixed &f) const { return val >= f.val; }

    bool operator==(const Fixed &f) const { return val == f.val; }

    bool operator!=(const Fixed &f) const { return val != f.val; }


#undef self
};

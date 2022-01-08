#pragma once

#include <iostream>
#include <bitset>

/**
 * this Qmn fixed point simulator
 * value range is from -2^(m-1) inclusive to +2^(m-1) exclusive
 * quantize precision is 2^(-n)
 *
 * it use 128-bit signed value to hold all bits so (m+n<=128)
 * all operations are implemented by real methods like shifting and addition
 * previous hack (use long double underhook are wiped)
 *
 * a v*(2^n) 2's complement version of result
 * ATTENTION: Due to typing limits and how c++ templates
 * works all of +|-|*|/ return Qmn from LHS (RHS auto cast to it)
 * which is what exactly is a fixed-point Qmn precision system
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
    using INNER_U = unsigned __int128;
    using INNER_I = signed __int128;
    using INNER_F = long double;

    static inline INNER_I mask(INNER_I inp) {
        const INNER_I signbit = (INNER_U) 1 << (m + n - 1);
        const INNER_I usable = ((INNER_U) 1 << (m + n)) - 1;
        return (inp & usable) | (!(inp & signbit) ? 0 : ~usable);
    }

    static inline std::bitset<n> mask_frac(INNER_I inp) {
        return inp & ((1 << n) - 1);
    }

    static inline std::bitset<m> mask_int(INNER_I inp) {
        return (inp >> n) & ((1 << m) - 1);
    }

    static INNER_F i2f(INNER_I vi) {
        // return vi / (INNER_F) (1 << n);

        const INNER_U signbit = (INNER_U) 1 << (m + n - 1);
        const auto sign = (vi & signbit) != 0;
        const INNER_U vu = sign ? -vi : vi;

        INNER_F res = vu >> n;
        for (auto i = 0; i < n; ++i) {
            const INNER_U mask = ((INNER_U) 1) << i;
            if (vu & mask) {
                res += powl(2, -n + i);
            }
        }
        return sign ? -res : res;
    }

    static INNER_I f2i(INNER_F v) {
        // return v * (1 << n);
        const auto sign = v < 0;
        auto vf = sign ? -v : v;
        auto vu = (INNER_U) vf;
        vf -= (INNER_F) vu;
        vf = vf * powl(2, n);
        vu = vu << n | (INNER_U) vf;
        return sign ? -vu : vu;
    }

    static Fixed fromRaw(INNER_I raw) {
        Fixed tmp;
        tmp.val = mask(raw);
        return tmp;
    }

    friend std::ostream &operator<<(std::ostream &os, const Fixed<m, n> &f) {
        return os << "Fixed[" << m << "," << n << "]("
                  << (INNER_F) f << " ~ "
                  // << std::bitset<8 * sizeof(INNER_I)>(f.val)
                  << mask_int(f.val) << "." << mask_frac(f.val)
                  << ")";
    }

private:
    INNER_I val = 0;

public:
    Fixed() : val(0) {}

    Fixed(const Fixed &f) : val(mask(f.val)) {}

    /** cross precision conversion */
    template<int mm, int nn>
    Fixed(const Fixed<mm, nn> &f) // NOLINT(google-explicit-constructor)
            : val(nn > n ? f.getRawBits() >> (nn - n) : f.getRawBits() << (n - nn)) {}

    Fixed(INNER_I v) : val(mask(v << n)) {} // NOLINT(google-explicit-constructor)

    Fixed(INNER_F v) : val(mask(f2i(v))) {} // NOLINT(google-explicit-constructor)

    Fixed(long long int v) : Fixed((INNER_I) v) {} // NOLINT(google-explicit-constructor)

    Fixed(long int v) : Fixed((INNER_I) v) {} // NOLINT(google-explicit-constructor)

    Fixed(int v) : Fixed((INNER_I) v) {} // NOLINT(google-explicit-constructor)

    Fixed(short v) : Fixed((INNER_I) v) {} // NOLINT(google-explicit-constructor)

    Fixed(char v) : Fixed((INNER_I) v) {} // NOLINT(google-explicit-constructor)

    Fixed(double v) : Fixed((INNER_F) v) {} // NOLINT(google-explicit-constructor)

    Fixed(float v) : Fixed((INNER_F) v) {} // NOLINT(google-explicit-constructor)

    ~Fixed() = default;

    explicit operator INNER_I() const { return self.val >> n; }

    explicit operator long long int() const { return (INNER_I) self; }

    explicit operator long int() const { return (INNER_I) self; }

    explicit operator int() const { return (INNER_I) self; }

    explicit operator short() const { return (INNER_I) self; }

    explicit operator char() const { return (INNER_I) self; }

    explicit operator INNER_F() const { return i2f(self.val); }

//    explicit operator long double() const { return (INNER_F) self; }

    explicit operator double() const { return (INNER_F) self; }

    explicit operator float() const { return (INNER_F) self; }

    explicit operator std::bitset<n + m>() const { return mask(val); }

    INNER_I getRawBits() const { return val; }

    void setRawBits(INNER_I const raw) { val = mask(raw); }

    Fixed operator>>(int v) const { return Fixed::fromRaw(self.val >> v); }

    Fixed operator<<(int v) const { return Fixed::fromRaw(self.val << v); }

    Fixed operator+(const Fixed &f) const { return Fixed::fromRaw(self.val + f.val); }

    Fixed operator-(const Fixed &f) const { return Fixed::fromRaw(self.val - f.val); }

    Fixed operator-() const { return Fixed::fromRaw(-self.val); }

    Fixed operator*(const Fixed &f) const {
        return Fixed::fromRaw(((INNER_I) self.val * (INNER_I) f.val) >> n);
    }

    Fixed operator/(const Fixed &f) const {
        return Fixed::fromRaw(((INNER_I) self.val << n) / (INNER_I) f.val);
    }

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

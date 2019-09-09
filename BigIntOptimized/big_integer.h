#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include "vector.h"
#include <string>


class big_integer {
    bool sign;
    vector <uint32_t> arr;


    void normalize();

    big_integer(bool sgn, vector <uint32_t> data);

    explicit big_integer(uint32_t x);

    vector <uint32_t> addition_to_2() const;

    big_integer addition_to_2_vice_versa() const;

    bool less_shifted(const big_integer& x, size_t shift);

    void subtract_shifted(const big_integer& x, size_t shift);
    
    big_integer operator*(uint32_t x);

    std::pair <big_integer, uint32_t> div_mod_short(uint32_t x) const;

public:
    uint32_t get(size_t i) const;

    int get_sign() const;
    
    big_integer();

    big_integer(const big_integer& w);

    big_integer(int x);
    
    big_integer& operator=(const big_integer& x);

    explicit big_integer(const std::string& s);
    
    
    friend bool operator==(const big_integer& w, const big_integer& q);

    friend bool operator!=(const big_integer& w, const big_integer& q);

    friend bool operator<(const big_integer& w, const big_integer& q);

    friend bool operator<=(const big_integer& w, const big_integer& q);

    friend bool operator>(const big_integer& w, const big_integer& q);

    friend bool operator>=(const big_integer& w, const big_integer& q);

    friend big_integer operator+(const big_integer& q);

    friend big_integer operator-(const big_integer& q);

    friend big_integer operator~(const big_integer& q);

    friend big_integer operator+(const big_integer& w, const big_integer& q);

    friend big_integer operator-(big_integer w, const big_integer& q);

    friend big_integer operator|(const big_integer& w, const big_integer& q);

    friend big_integer operator&(const big_integer& w, const big_integer& q);

    friend big_integer operator^(const big_integer& w, const big_integer& q);

    friend big_integer operator<<(const big_integer& q, uint32_t x);

    friend big_integer operator>>(const big_integer& q, uint32_t x);

    friend std::pair <big_integer, big_integer> div_mod (const big_integer& w, const big_integer& q);

    friend big_integer operator* (const big_integer& w, const big_integer& q);

    friend big_integer operator/ (const big_integer& w, const big_integer& q);

    friend big_integer operator%(const big_integer& w, const big_integer& q);

    friend big_integer& operator+=(big_integer& w, const big_integer& q);

    friend big_integer& operator-=(big_integer& w, const big_integer& q);

    friend big_integer& operator*=(big_integer& w, const big_integer& q);

    friend big_integer& operator/=(big_integer& w, const big_integer& q);

    friend big_integer& operator%=(big_integer& w, const big_integer& q);

    friend big_integer& operator&=(big_integer& w, const big_integer& q);

    friend big_integer& operator|=(big_integer& w, const big_integer& q);

    friend big_integer& operator^=(big_integer& w, const big_integer& q);

    friend big_integer& operator<<=(big_integer& w, uint32_t q);

    friend big_integer& operator>>=(big_integer& w, uint32_t q);
    
    friend std::string to_string(const big_integer& q);
};


#endif // BIG_INTEGER_H

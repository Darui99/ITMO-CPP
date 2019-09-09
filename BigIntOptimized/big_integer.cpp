#include "big_integer.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstddef>

const uint INF = std::numeric_limits <uint>::max();

void big_integer::normalize() {
    while (arr.size() > 1) {
        if (arr.back() == 0)
            arr.pop_back();
        else
            break;
    }
    if (arr.size() == 1 && arr.back() == 0)
        sign = 0;
}

big_integer::big_integer(bool sgn, vector <uint32_t> data) {
    sign = sgn;
    arr = data;
}

big_integer::big_integer() {
    sign = 0;
    arr.resize(1, 0);
}

big_integer::big_integer(const big_integer& w) {
    sign = w.sign;
    arr = w.arr;
}

big_integer::big_integer(int x) {
    if (x == -2147483648) {
        sign = 1;
        arr.resize(1, static_cast<uint32_t>(2147483648));
        return;
    }
    if (x < 0) {
        sign = 1;
        x = -x;
    } else {
        sign = 0;
    }
    arr.resize(1, x);
}

big_integer::big_integer(uint32_t x) {
    sign = 0;
    arr.resize(1, x);
}

big_integer& big_integer::operator=(const big_integer& x) {
    arr = x.arr;
    sign = x.sign;
    return *this;
}

big_integer::big_integer(const std::string& s) {
    big_integer res = big_integer();
    sign = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            sign = 1;
            continue;
        }
        res = res * 10 + (int) (s[i] - '0');
    }
    arr = res.arr;
    this->normalize();
}

vector <uint32_t> big_integer::addition_to_2() const {
    vector<uint32_t> res = arr;
    res.push_back(0);

    if (sign == 1) {
        for (size_t i = 0; i < res.size(); i++)
            res[i] = ~res[i];
        return (big_integer(0, res) + 1).arr;
    } else {
        return res;
    }
}

big_integer big_integer::addition_to_2_vice_versa() const {
    vector<uint32_t> x = arr;
    uint32_t sign = x.back();
    while (x.size() > 1 && x.back() == sign)
        x.pop_back();

    if (x.size() == 1 && x.back() == 0)
        return big_integer();

    vector<uint32_t> res;

    if (sign == 0)
        res = x;
    else {
        res = (big_integer(0, x) - 1).arr;
        for (size_t i = 0; i < res.size(); i++)
            res[i] = ~res[i];
    }

    big_integer ans = big_integer((sign == 0 ? 0 : 1), res);    ans.normalize();
    return ans;
}

bool big_integer::less_shifted(const big_integer &x, size_t shift) {
	if (x == 0) {
		return false;
	}
    if (arr.size() < x.arr.size() + shift)
        return true;
    if (arr.size() > x.arr.size() + shift)
        return false;
    for (ptrdiff_t i = x.arr.size() - 1; i >= 0; i--) {
        if (arr[i + shift] < x.arr[i])
            return true;
        if (arr[i + shift] > x.arr[i])
            return false;
    }
    return false;
}

void big_integer::subtract_shifted(const big_integer &x, size_t shift) {
    uint32_t cur_carry = 0, next_carry = 0, a, b;
    for (size_t i = shift; i < arr.size(); i++) {
        cur_carry = next_carry; next_carry = 0;
        a = arr[i];
        b = (i - shift < x.arr.size() ? x.arr[i - shift] : 0);

        arr[i] = a - b;
        if (a < b) {
            next_carry = 1;
        }
        else {
            if (arr[i] < cur_carry) {
                next_carry = 1;
            }
        }
        arr[i] -= cur_carry;
    }

    normalize();
}

big_integer big_integer::operator*(uint32_t x) {
    vector <uint32_t> res(arr.size());
    uint64_t cur = 0, carry = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        cur = (uint64_t)arr[i] * (uint64_t)x + carry;
        res[i] = static_cast<uint32_t>(cur & ((1ll << 32) - 1));
        carry = (cur >> 32);
    }
    if (carry > 0)
        res.push_back(static_cast<const uint32_t>(carry));
    big_integer ans = big_integer(sign, res);
    ans.normalize();
    return ans;
}

std::pair<big_integer, uint32_t> big_integer::div_mod_short(uint32_t x) const {
    vector <uint32_t> res(arr.size());
    vector <uint32_t> y = this->arr;
    uint64_t cur = 0;
    for (ptrdiff_t i = res.size() - 1; i >= 0; i--) {
        cur = cur * (uint64_t)(INF + 1ll) + y[i];
        res[i] = static_cast<uint32_t>(cur / x);
        cur %= x;
    }
    big_integer ans = big_integer(sign, res);
    ans.normalize();
    return std::make_pair(ans, cur);
}

uint32_t big_integer::get(size_t i) const {
    return arr[i];
}

int big_integer::get_sign() const {
    return sign;
}

bool operator==(const big_integer& w, const big_integer& q) {
    return (w.arr == q.arr && w.sign == q.sign);
}

bool operator!=(const big_integer& w, const big_integer& q) {
    return !(w == q);
}

bool operator<(const big_integer& w, const big_integer& q) {
    if (w.sign == 0 && q.sign == 1)
        return false;
    if (w.sign == 1 && q.sign == 0)
        return true;
    if (w.sign == 1 && q.sign == 1)
        return (-w > -q);

    if (w.arr.size() < q.arr.size())
        return true;
    if (w.arr.size() > q.arr.size())
        return false;

    for (ptrdiff_t i = w.arr.size() - 1; i >= 0; i--) {
        if (w.arr[i] < q.arr[i])
            return true;
        if (w.arr[i] > q.arr[i])
            return false;
    }
    return false;
}

bool operator>(const big_integer& w, const big_integer& q) {
    if (w.sign == 0 && q.sign == 1)
        return true;
    if (w.sign == 1 && q.sign == 0)
        return false;
    if (w.sign == 1 && q.sign == 1)
        return (-w < -q);

    if (w.arr.size() > q.arr.size())
        return true;
    if (w.arr.size() < q.arr.size())
        return false;

    for (ptrdiff_t i = w.arr.size() - 1; i >= 0; i--) {
        if (w.arr[i] > q.arr[i])
            return true;
        if (w.arr[i] < q.arr[i])
            return false;
    }
    return false;
}

bool operator<=(const big_integer& w, const big_integer& q) {
    return (w < q || w == q);
}

bool operator>=(const big_integer& w, const big_integer& q) {
    return (w > q || w == q);
}

big_integer operator+(const big_integer& q) {
    return big_integer(q.sign, q.arr);
}

big_integer operator-(const big_integer& q) {
    big_integer ans = big_integer(!q.sign, q.arr);
    ans.normalize();
    return ans;
}

big_integer operator+(const big_integer& w, const big_integer& q) {
    if (w.sign == 0 && q.sign == 1)
        return w - -q;
    if (w.sign == 1 && q.sign == 0)
        return q - -w;

    vector <uint32_t> res(std::max(w.arr.size(), q.arr.size()));

    uint32_t cur_carry = 0, next_carry = 0, a, b;
    for (size_t i = 0; i < res.size(); i++) {
        cur_carry = next_carry; next_carry = 0;
        a = (i < w.arr.size() ? w.arr[i] : 0);
        b = (i < q.arr.size() ? q.arr[i] : 0);

        res[i] = a + b;
        if (a > INF - b) {
            next_carry = 1;
        }
        else {
            if (res[i] > INF - cur_carry) {
                next_carry = 1;
            }
        }
        res[i] += cur_carry;
    }
    if (next_carry > 0)
        res.push_back(next_carry);

    big_integer ans = big_integer(q.sign, res);
    ans.normalize();
    return ans;
}

big_integer operator-(big_integer w, const big_integer& q) {
    return w -= q;
}

big_integer operator*(const big_integer& w, const big_integer& q) {
    if (w.arr.size() < q.arr.size())
        return q * w;
    big_integer res, cur, W;
    W = (w.sign == 0 ? w : -w);

    for (ptrdiff_t i = q.arr.size() - 1; i >= 0; i--) {
        cur = W * q.arr[i];
        res = (res << 32) + cur;
    }
    res.sign = (w.sign ^ q.sign);
    res.normalize();
    return res;
}

big_integer operator|(const big_integer& w, const big_integer& q) {
    vector <uint32_t> y = w.addition_to_2(), x = q.addition_to_2();
    vector <uint32_t> res(std::max(y.size(), x.size()));
    uint32_t a, b;
    for (size_t i = 0; i < res.size(); i++) {
        a = (i < y.size() ? y[i] : (w.sign == 0 ? 0 : INF));
        b = (i < x.size() ? x[i] : (q.sign == 0 ? 0 : INF));
        res[i] = a | b;
    }
    return big_integer(0, res).addition_to_2_vice_versa();
}

big_integer operator&(const big_integer& w, const big_integer& q) {
    vector <uint32_t> y = w.addition_to_2(), x = q.addition_to_2();
    vector <uint32_t> res(std::max(y.size(), x.size()));
    uint32_t a, b;
    for (size_t i = 0; i < res.size(); i++) {
        a = (i < y.size() ? y[i] : (w.sign == 0 ? 0 : INF));
        b = (i < x.size() ? x[i] : (q.sign == 0 ? 0 : INF));
        res[i] = a & b;
    }
    return big_integer(0, res).addition_to_2_vice_versa();
}

big_integer operator^(const big_integer& w, const big_integer& q) {
    vector <uint32_t> y = w.addition_to_2(), x = q.addition_to_2();
    vector <uint32_t> res(std::max(y.size(), x.size()));
    uint32_t a, b;
    for (size_t i = 0; i < res.size(); i++) {
        a = (i < y.size() ? y[i] : (w.sign == 0 ? 0 : INF));
        b = (i < x.size() ? x[i] : (q.sign == 0 ? 0 : INF));
        res[i] = a ^ b;
    }
    return big_integer(0, res).addition_to_2_vice_versa();
}

big_integer operator~(const big_integer& q) {
    vector <uint32_t> res = q.addition_to_2();
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = ~res[i];
    }
    return big_integer(0, res).addition_to_2_vice_versa();
}

big_integer operator<<(const big_integer& q, uint32_t x) {
    uint32_t carry, d = x % 32;
    vector <uint32_t> arr = q.addition_to_2(), res;
    if (d > 0) {
        arr.push_back((q.sign == 0 ? 0 : INF));
        arr.back() &= INF - (static_cast<uint32_t>((1 << d)) - 1);
        for (ptrdiff_t i = arr.size() - 2; i >= 0; i--) {
            carry = 0;
            for (ptrdiff_t j = 31; j > 31 - d; j--) {
                carry = carry * 2 + (((1 << j) & arr[i]) > 0);
            }
            arr[i + 1] += carry;
            arr[i] <<= d;
        }
    }
    res.resize(x / 32 + arr.size());
    for (size_t i = 0; i < arr.size(); i++)
        res[x / 32 + i] = arr[i];
    return big_integer(0, res).addition_to_2_vice_versa();
}

big_integer operator>>(const big_integer& q, uint32_t x) {
    uint32_t carry, d = x % 32;
    if (d == 0) {
        vector<uint32_t> arr = q.arr;
        for (size_t i = 0; i < x / 32; i++)
            arr.erase(0);
        return big_integer(q.sign, arr);
    }
    vector<uint32_t> arr = q.addition_to_2();
    if (x / 32 >= arr.size()) {
        return (q.sign == 0 ? big_integer(0) : big_integer(-1));
    }

    for (size_t i = x / 32; i < arr.size(); i++) {
        carry = 0;
        for (size_t j = 0; j < d; j++)
            carry += ((1 << j) & arr[i]);
        if (i > 0) {
            arr[i - 1] += (carry << (32 - d));
        }
        arr[i] >>= d;
    }

    if (q.sign == 1) {
        arr.back() += ((static_cast<uint32_t>((1 << d)) - 1) << (32 - d));
    }
    vector<uint32_t> res(arr.size() - x / 32);
    for (size_t i = x / 32, j = 0; i < arr.size(); i++, j++)
        res[j] = arr[i];
    return big_integer(0, res).addition_to_2_vice_versa();
}

std::pair <big_integer, big_integer> div_mod (const big_integer& w, const big_integer& q) {
    big_integer a = (w.sign ? -w : w), b = (q.sign ? -q : q), diff;

    if (a < b) {
        return std::make_pair(0, (w.sign == q.sign ? w : w + q));
    }

    if (q.arr.size() == 1) {
        std::pair <big_integer, uint32_t> res = w.div_mod_short(q.arr[0]);
        big_integer second = big_integer(res.second);
        second.sign = w.sign;
        res.first.sign = (w.sign ^ q.sign);
        res.first.normalize();
        second.normalize();
        return std::make_pair(res.first, second);
    }

    uint32_t step = 0, curB = b.arr.back();
    while(curB < (uint32_t)(1 << 31)) {
        curB <<= 1;
        step++;
    }

    a <<= step;
    b <<= step;

    size_t m = a.arr.size() - b.arr.size();
    vector <uint32_t> res(m + 1);
    if (a >= (b << (m * 32))) {
        res[m] = 1;
        a = a - (b << (m * 32));
    }

    for (ptrdiff_t i = m - 1; i >= 0; i--) {
        uint64_t now;
        if (a.arr.size() > 1)
            now = (static_cast<uint64_t>((1ull << 32) * a.arr.back()) + a.arr[a.arr.size() - 2]) / b.arr.back();
        else
            now = static_cast<uint64_t>(a.arr.back()) / static_cast<uint64_t>(b.arr.back());
        if (now > (1ll << 32) - 1)
            now = (1ll << 32) - 1;

        res[i] = static_cast<uint32_t>(now);
        diff = b * res[i];
        while(a.less_shifted(diff, static_cast<size_t>(i))) {
            res[i]--;
            diff -= b;
        }
        a.subtract_shifted(diff, static_cast<size_t>(i));
    }

    a >>= step;
    a.sign = w.sign;
    a.normalize();

    big_integer ans = big_integer((w.sign ^ q.sign), res);
    ans.normalize();
    return std::make_pair(ans, a);
}

big_integer operator/(const big_integer& w, const big_integer& q) {
    return div_mod(w, q).first;
}

big_integer operator%(const big_integer& w, const big_integer& q) {
    return div_mod(w, q).second;
}

big_integer& operator+=(big_integer& w, const big_integer& q) {
    w = w + q;
    return w;
}

big_integer& operator-=(big_integer& w, const big_integer& q) {
    if (w.sign == 0 && q.sign == 1) {
        w += -q;
        return w;
    }
    if (w.sign == 1 && q.sign == 0) {
        w = -(-w + q);
        return w;
    }
    if (w.sign == 1 && q.sign == 1) {
        w = -(-w - -q);
        return w;
    }
    if (w < q) {
        w = -(q - w);
        return w;
    }

    uint32_t cur_carry = 0, next_carry = 0, a, b;
    for (size_t i = 0; i < w.arr.size(); i++) {
        cur_carry = next_carry; next_carry = 0;
        a = (i < w.arr.size() ? w.arr[i] : 0);
        b = (i < q.arr.size() ? q.arr[i] : 0);
        
        if (i >= q.arr.size() && cur_carry == 0)
			break;

        w.arr[i] = a - b;
        if (a < b) {
            next_carry = 1;
        }
        else {
            if (w.arr[i] < cur_carry) {
                next_carry = 1;
            }
        }
        w.arr[i] -= cur_carry;
    }

    w.normalize();
    return w;
}

big_integer& operator*=(big_integer& w, const big_integer& q) {
    w = w * q;
    return w;
}

big_integer& operator/=(big_integer& w, const big_integer& q) {
    w = w / q;
    return w;
}

big_integer& operator%=(big_integer& w, const big_integer& q) {
    w = w % q;
    return w;
}

big_integer& operator&=(big_integer& w, const big_integer& q) {
    w = w & q;
    return w;
}

big_integer& operator|=(big_integer& w, const big_integer& q) {
    w = w | q;
    return w;
}

big_integer& operator^=(big_integer& w, const big_integer& q) {
    w = w ^ q;
    return w;
}

big_integer& operator<<=(big_integer& w, uint32_t q) {
    w = w << q;
    return w;
}

big_integer& operator>>=(big_integer& w, uint32_t q) {
    w = w >> q;
    return w;
}

std::string to_string(const big_integer& q) {
    if (q == big_integer(0)) {
        return "0";
    }
    big_integer x = (q.get_sign() == 0 ? q : -q);
    std::string res = "";
    while (x > 0) {
        std::pair <big_integer, uint32_t> div_mod_10 = x.div_mod_short(10);
        uint32_t cur = div_mod_10.second;
        res.push_back((char)(cur + '0'));
        x = div_mod_10.first;
    }
    if (q.get_sign() == 1)
        res.push_back('-');
    reverse(res.begin(), res.end());
    return res;
}

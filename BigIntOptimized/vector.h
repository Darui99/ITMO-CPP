//
// Created by darui99 on 16.05.19.
//

#ifndef BIGINTSIGNATURES_VECTOR_H
#define BIGINTSIGNATURES_VECTOR_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>

template <typename T>
class vector {
    static const size_t small_size = 16;

    size_t size_;
    bool small;

    T small_arr[small_size];
    std::shared_ptr < std::vector<T> > big_arr;

    void born() {
        big_arr = std::shared_ptr < std::vector<T> > (new std::vector<T>(*big_arr.get()));
    }

    void normalize() {
        if (big_arr.use_count() > 1)
            born();
    }

    void constriction() {
        for (size_t i = 0; i < (*big_arr.get()).size(); i++)
            small_arr[i] = (*big_arr.get())[i];
        small = true;
    }

    void expansion() {
        if (big_arr == nullptr) {
            big_arr = std::shared_ptr< std::vector<T> > (new std::vector <T>());
        }
        normalize();
        (*big_arr.get()).resize(size_);
        for (size_t i = 0; i < size_; i++)
            (*big_arr.get())[i] = small_arr[i];
        small = false;
    }

public:

    vector() {
        big_arr = nullptr;
        size_ = 0;
        small = true;
    }

    vector(size_t x) : vector() {
        if (x > small_size) {
            big_arr = std::shared_ptr< std::vector<T> > (new std::vector <T>());
            (*big_arr.get()).resize(x);
            small = false;
        } else {
            for (size_t i = 0; i < x; i++)
                small_arr[i] = 0;
        }
        size_ = x;
    }

    vector (const vector<T> &x) : vector() {
        for (size_t i = 0; i < small_size; i++)
            small_arr[i] = x.small_arr[i];
        big_arr = x.big_arr;
        small = x.small;
        size_ = x.size();
    }

    vector& operator= (const vector &x) {
        for (size_t i = 0; i < small_size; i++)
            small_arr[i] = x.small_arr[i];
        big_arr = x.big_arr;
        small = x.small;
        size_ = x.size();
        return (*this);
    }

    bool operator== (const vector &x) const {
        if (size_ != x.size())
            return false;
        if (small) {
            bool res = true;
            for (size_t i = 0; i < size_; i++)
                res &= (small_arr[i] == x[i]);
            return res;
        } else {
            bool res = true;
            for (size_t i = 0; i < size_; i++)
                res &= ((*big_arr.get())[i] == x[i]);
            return res;
        }
    }

    size_t size() const {
        return size_;
    }

    T operator[](const size_t i) const {
        if (small)
            return small_arr[i];
        else
            return (*big_arr.get())[i];
    }

    T& operator[](size_t i) {
        if (small)
            return small_arr[i];
        normalize();
        return (*big_arr.get())[i];
    }

    T& back() {
        if (small) {
            return small_arr[size_ - 1];
        } else {
            normalize();
            return (*big_arr.get()).back();
        }
    }

    void push_back(const T x) {
        if (small) {
            if (size_ == small_size) {
                expansion();
                (*big_arr.get()).push_back(x);
            } else {
                small_arr[size_] = x;
            }
        } else {
            normalize();
            (*big_arr.get()).push_back(x);
        }
        size_++;
    }

    void pop_back() {
        if (!small) {
            if ((*big_arr.get()).size() == small_size / 2)
                constriction();
            else {
                normalize();
                (*big_arr.get()).pop_back();
            }
        }
        size_--;
    }

    void resize(const size_t x) {
        if (x == size_)
            return;
        if (x > size_) {
            if (!small || (small && x > small_size)) {
                if (small)
                    expansion();
                normalize();
                (*big_arr.get()).resize(x);
            } else {
                for (size_t i = size_; i < x; i++)
                    small_arr[i] = 0;
            }
        } else {
            if (!small) {
                normalize();
                (*big_arr.get()).resize(x);
                if (x < small_size / 2)
                    constriction();
            }
        }
        size_ = x;
    }

    void resize(const size_t x, const T val) {
        if (x == size_)
            return;
        if (x > size_) {
            if (!small || (small && x > small_size)) {
                if (small)
                    expansion();
                normalize();
                (*big_arr.get()).resize(x, val);
            } else {
                for (size_t i = size_; i < x; i++)
                    small_arr[i] = val;
            }
        } else {
            if (!small) {
                normalize();
                (*big_arr.get()).resize(x);
                if (x < small_size / 2)
                    constriction();
            }
        }
        size_ = x;
    }

    void erase(size_t x) {
        if (small) {
            for (size_t i = x + 1; i < size_; i++)
                std::swap(small_arr[i - 1], small_arr[i]);
        } else {
            normalize();
            (*big_arr.get()).erase((*big_arr.get()).begin() + x);
            if ((*big_arr.get()).size() < small_size / 2)
                constriction();
        }
        size_--;
    }
};

#endif //BIGINTSIGNATURES_VECTOR_H

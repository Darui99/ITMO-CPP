//
// Created by darui99 on 15.06.19.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <cstring>
#include <new>

template <typename T>
struct vector {

    typedef T value_type;

    typedef T* iterator;

    typedef T const * const_iterator;

    typedef std::reverse_iterator<T*> reverse_iterator;

    typedef std::reverse_iterator<T const *> const_reverse_iterator;

    iterator begin() noexcept {
        normalize();
        return arr_;
    }

    const_iterator begin() const noexcept {
        return arr_;
    }

    iterator end() noexcept {
        normalize();
        return (arr_ + size());
    }

    const_iterator end() const noexcept {
        return (arr_ + size());
    }

    reverse_iterator rbegin() noexcept {
        normalize();
        return std::reverse_iterator<T*>(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return std::reverse_iterator<T const *>(end());
    }

    reverse_iterator rend() noexcept {
        normalize();
        return std::reverse_iterator<T*>(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return std::reverse_iterator<T const *>(begin());
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        clear();
        while (first != last) {
            push_back(*first);
            first++;
        }
    }

    vector() noexcept {
        arr_ = nullptr;
    }

    ~vector() noexcept {
        kill_la_kill();
    }

    vector (vector<T> const & arg) {
        if (!arg.is_small()) {
            arr_ = arg.arr_;
            buf.big_arr = arg.buf.big_arr;
            ((size_t*)buf.big_arr)[0]++;
        } else {
            if (!arg.empty()) {
                new(&buf.small_arr) T(arg.buf.small_arr);
                arr_ = (T*)&buf;
            } else {
                arr_ = nullptr;
            }
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector() {
        while (first != last) {
            push_back(*first);
            first++;
        }
    }

    vector<T>& operator=(vector<T> const & arg) {
        if (&(*this) == &arg)
            return (*this);
        vector <T> cop(arg);
        swap((*this), cop);
        return (*this);
    }


    size_t size() const noexcept {
        if (is_small()) {
            if (arr_ == nullptr)
                return 0;
            return 1;
        }
        return ((size_t*)buf.big_arr)[1];
    }

    size_t capacity() const noexcept {
        if (is_small()) {
            return 1;
        }
        return ((size_t*)buf.big_arr)[2];
    }

    bool empty() const noexcept {
        return (size() == 0);
    }

    T const & operator[] (size_t ind) const noexcept {
        if (is_small())
            return buf.small_arr;
        return arr_[ind];
    }

    T& operator[] (size_t ind) {
        if (is_small())
            return buf.small_arr;
        normalize();
        return arr_[ind];
    }

    T const & back() const noexcept {
        return (*this)[size() - 1];
    }

    T& back() {
        return (*this)[size() - 1];
    }

    T const & front() const noexcept {
        return (*this)[0];
    }

    T& front() {
        return (*this)[0];
    }

    void push_back(T const arg) {
        if (is_small()) {
            if (size() == 0) {
                arr_ = (T*)&buf;
                try {
                    new(&buf.small_arr) T(arg);
                } catch (...) {
                    arr_ = nullptr;
                    throw;
                }
                return;
            }
            expansion();
        }
        normalize();
        /*vector <T> cop(*this);
        if (cop.size() == cop.capacity())
            cop.set_capacity(cop.capacity() * 2);
        new (cop.arr_ + cop.size()) T(arg);
        swap((*this), cop);*/
        bool flag = false;
        if (size() == capacity()) {
            set_capacity(capacity() * 2);
            flag = true;
        }
        try {
            new(arr_ + size()) T(arg);
        } catch (...) {
            if (flag) {
                //realloc(buf.big_arr, sizeof(size_t) * 3 + sizeof(T) * capacity() / 2);
                //((size_t*)buf.big_arr)[2] /= 2;
                //set_capacity(capacity() / 2);
            }
            throw;
        }
        ((size_t*)buf.big_arr)[1]++;
    }

    void pop_back() {
        if (is_small()) {
            if (arr_ != nullptr) {
                buf.small_arr.~T();
                arr_ = nullptr;
            }
            return;
        }
        normalize();
        arr_[size() - 1].~T();
        ((size_t*)buf.big_arr)[1]--;
    }

    void clear() {
        if (is_small()) {
            if (size() == 1)
                pop_back();
            arr_ = nullptr;
        } else {
            normalize();
            for (size_t i = 0; i < size(); i++)
                (*this)[i].~T();
            ((size_t*)buf.big_arr)[1] = 0;
        }
    }

    void shrink_to_fit() {
        if (is_small())
            return;
        normalize();
        set_capacity(size());
    }

    void reserve(size_t arg) {
        if (is_small()) {
            expansion();
        }
        normalize();
        set_capacity(arg);
    }

    void resize(size_t sz, T const & val) {
        vector <T> cop((*this));
        if (sz >= cop.size()) {
            while(cop.size() < sz)
                cop.push_back(val);
        } else {
            while(cop.size() > sz)
                cop.pop_back();
        }
        swap((*this), cop);
    }

    T const* data() const noexcept {
        if (empty())
            return nullptr;
        if (is_small()) {
            return &buf.small_arr;
        } else {
            return arr_;
        }
    }

    T* data() {
        if (empty())
            return nullptr;
        if (is_small()) {
            return &buf.small_arr;
        } else {
            normalize();
            return arr_;
        }
    }

    iterator insert(const_iterator pos, T const& val) {
        size_t ind = (pos - begin());
        push_back(val);
        if (is_small())
            return begin();
        normalize();
        pos = (begin() + ind);
        iterator it = end(); it--;
        while (it != pos) {
            std::swap(*it, *(it - 1));
            it--;
        }
        return it;
    }

    iterator erase(const_iterator pos) {
        if (is_small()) {
            pop_back();
            return nullptr;
        }
        normalize();
        size_t ind = (pos - begin());
        iterator it = (begin() + ind); it++;
        while (it != end()) {
            std::swap(*it, *(it - 1));
            it++;
        }
        pop_back();
        return (begin() + ind);
    }

    iterator erase(const_iterator first, const_iterator last) {
        if (is_small()) {
            pop_back();
            return nullptr;
        }
        normalize();
        size_t indf = (first - begin()), indl = (last - begin());
        iterator it = (begin() + indl), itf = (begin() + indf), itl = (begin() + indl);
        iterator res = it;
        while (it != end()) {
            std::swap(*it, *(itf + (it - itl)));
            it++;
        }
        for (size_t i = 0; i < indl - indf; i++)
            pop_back();
        return res;
    }

    template <typename U>
    friend void swap(vector<U> & a, vector<U> & b);

private:

    union twin {
        void* big_arr;
        T small_arr;

        twin() {
            big_arr = nullptr;
        }

        ~twin() {

        }
    };

    T* arr_;
    twin buf;

    void kill_la_kill() {
        if (is_small()) {
            if (arr_ != nullptr)
                buf.small_arr.~T();
            return;
        }
        ((size_t*)buf.big_arr)[0]--;
        if (link_count() == 0) {
            for (size_t i = 0; i < size(); i++)
                (*this)[i].~T();
            free(buf.big_arr);
        }
    }

    bool is_small() const noexcept {
        return (arr_ == nullptr || arr_ == (T*)&buf);
    }

    size_t link_count() const noexcept {
        if (is_small()) {
            return 0;
        }
        return ((size_t*)buf.big_arr)[0];
    }

    void born() {
        size_t ccp = capacity(), csz = size();
        size_t need = sizeof(size_t) * 3 + ccp * sizeof(T);
        void* new_arr = malloc(need);
        if (new_arr == nullptr)
            throw std::bad_alloc();
        std::memcpy(new_arr, buf.big_arr, sizeof(size_t) * 3);
        ((size_t*)buf.big_arr)[0]--;
        size_t complete = 0;
        try {
            for (; complete < csz; complete++)
                new((T *) ((size_t *) (new_arr) + 3) + complete)  T(arr_[complete]);
        } catch (...) {
            for (size_t i = 0; i < complete; i++)
                (*((T*)((size_t*)(new_arr) + 3) + i)).~T();
            free(new_arr);
            ((size_t*)buf.big_arr)[0]++;
            throw;
        }
        buf.big_arr = new_arr;
        arr_ = (T*)((size_t*)(buf.big_arr) + 3);
        ((size_t*)buf.big_arr)[0] = 1;
    }

    void normalize() {
        if (link_count() > 1)
            born();
    }

    void expansion() {
        size_t need = sizeof(size_t) * 3 + sizeof(T);
        void* new_arr = malloc(need);
        if (new_arr == nullptr)
            throw std::bad_alloc();
        bool emp = (arr_ == nullptr);
        ((size_t*)new_arr)[0] = 1;
        ((size_t*)new_arr)[1] = static_cast<size_t>(!emp);
        ((size_t*)new_arr)[2] = 1;
        if (!emp) {
            arr_ = (T*)((size_t*)(new_arr) + 3);
            try {
                new(arr_) T(buf.small_arr);
            } catch (...) {
                free(new_arr);
                arr_ = (T*)(&buf);
                throw;
            }
            buf.small_arr.~T();
        } else {
            arr_ = (T *) ((size_t *) (new_arr) + 3);
        }
        buf.big_arr = new_arr;
    }

    void set_capacity(size_t arg) {
        size_t need = sizeof(size_t) * 3 + sizeof(T) * arg, csz = size();
        void* new_arr = malloc(need);
        if (new_arr == nullptr)
            throw std::bad_alloc();
        std::memcpy(new_arr, buf.big_arr, sizeof(size_t) * 3);
        size_t complete = 0;
        try {
            for (; complete < std::min(csz, arg); complete++)
                new ((T *) ((size_t *) (new_arr) + 3) + complete)  T(arr_[complete]);
        } catch (...) {
            for (size_t i = 0; i < complete; i++)
                (*((T*)((size_t*)(new_arr) + 3) + i)).~T();
            free(new_arr);
            throw;
        }
        std::swap(buf.big_arr, new_arr);
        ((size_t*)buf.big_arr)[2] = arg;
        arr_ = (T*)((size_t*)(buf.big_arr) + 3);
        for (size_t i = 0; i < csz; i++)
            (*((T*)((size_t*)(new_arr) + 3) + i)).~T();
        free(new_arr);
    }
};

template <typename T>
bool operator==(const vector<T> & a, const vector<T> & b) {
    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

template <typename T>
bool operator!=(const vector<T> & a, const vector<T> & b) {
    return !(a == b);
}

template <typename T>
bool operator<(const vector<T> & a, const vector<T> & b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); i++) {
        if (a[i] < b[i])
            return true;
        if (a[i] > b[i])
            return false;
    }
    return (a.size() < b.size());
}

template <typename T>
bool operator<=(const vector<T> & a, const vector<T> & b) {
    return ((a < b) || (a == b));
}

template <typename T>
bool operator>(const vector<T> & a, const vector<T> & b) {
    return !(a <= b);
}

template <typename T>
bool operator>=(const vector<T> & a, const vector<T> & b) {
    return !(a < b);
}

template <typename T>
void swap(vector<T> & a, vector<T> & b) {
    if (a.empty() && b.empty())
        return;
    if (a.empty() && b.is_small()) {
        new (&a.buf.small_arr) T(b.buf.small_arr);
        b.buf.small_arr.~T();
        b.arr_ = nullptr;
        a.arr_ = (T*)&a.buf;
        return;
    }
    if (a.empty() && !b.is_small()) {
        a.buf.big_arr = b.buf.big_arr;
        std::swap(a.arr_, b.arr_);
        return;
    }
    if (a.is_small() && b.empty()) {
        new (&b.buf.small_arr) T(a.buf.small_arr);
        a.buf.small_arr.~T();
        a.arr_ = nullptr;
        b.arr_ = (T*)&b.buf;
        return;
    }
    if (!a.is_small() && b.empty()) {
        b.buf.big_arr = a.buf.big_arr;
        std::swap(a.arr_, b.arr_);
        return;
    }
    if (a.is_small() && b.is_small()) {
        std::swap(a.buf.small_arr, b.buf.small_arr);
        return;
    }
    if (a.is_small() && !b.is_small()) {
        std::swap(a.arr_, b.arr_);
        void* tp = b.buf.big_arr;
        try {
            new(&b.buf.small_arr) T(a.buf.small_arr);
        } catch (...) {
            std::swap(a.arr_, b.arr_);
            throw;
        }
        a.buf.small_arr.~T();
        a.buf.big_arr = tp;
        b.arr_ = (T*)&b.buf;
        return;
    }
    if (!a.is_small() && b.is_small()) {
        std::swap(a.arr_, b.arr_);
        void* tp = a.buf.big_arr;
        try {
            new(&a.buf.small_arr) T(b.buf.small_arr);
        } catch (...) {
            std::swap(a.arr_, b.arr_);
            throw;
        }
        b.buf.small_arr.~T();
        b.buf.big_arr = tp;
        a.arr_ = (T*)&a.buf;
        return;
    }
    if (!a.is_small() && !b.is_small()) {
        std::swap(a.arr_, b.arr_);
        std::swap(a.buf.big_arr, b.buf.big_arr);
        return;
    }
}

#endif //VECTOR_VECTOR_H
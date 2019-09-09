//
// Created by darui99 on 22.06.19.
//

#ifndef EXAM_LIST_LIST_H
#define EXAM_LIST_LIST_H

#include <iostream>
#include <iterator>

template <typename T>
struct list {

private:
    struct node_base {
        node_base* next;
        node_base* prev;

        explicit node_base() noexcept {
            next = this;
            prev = this;
        }

        template <typename U>
        friend void swap(list<U> & a, list<U> & b);
    };

    struct node : node_base {
        T val;

        explicit node(const T &arg) : val(arg) {}
    };


    struct list_const_iterator {
        typedef T value_type;

        typedef list_const_iterator self_type;

        typedef const T& reference;

        typedef const T* pointer;

        typedef std::bidirectional_iterator_tag iterator_category;

        typedef int difference_type;

        list_const_iterator(std::nullptr_t) = delete;

        list_const_iterator(node_base* arg) : elem(arg) {}

        list_const_iterator operator++() {
            elem = elem->next;
            return *this;
        }

        list_const_iterator operator--() {
            elem = elem->prev;
            return *this;
        }

        list_const_iterator operator++(int) {
            list_const_iterator cur = *this;
            ++(*this);
            return cur;
        }

        list_const_iterator operator--(int) {
            list_const_iterator cur = *this;
            --(*this);
            return cur;
        }

        const T& operator*() const {
            return static_cast<node*>(elem)->val;
        }

        const T* operator->() const {
            return &static_cast<node*>(elem)->val;
        }

        bool operator==(const self_type& arg) const {
            return elem == arg.elem;
        }

        bool operator!=(const self_type& arg) const {
            return !(*this == arg);
        }

        friend list;

    private:
        node_base* elem = nullptr;
    };

    struct list_iterator {
        typedef T value_type;

        typedef list_iterator self_type;

        typedef T& reference;

        typedef T* pointer;

        typedef std::bidirectional_iterator_tag iterator_category;

        typedef int difference_type;

        list_iterator(std::nullptr_t) = delete;

        list_iterator(node_base* ptr) : elem(ptr) {}

        list_iterator operator++() {
            elem = elem->next;
            return *this;
        }

        list_iterator operator--() {
            elem = elem->prev;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator cur = *this;
            ++(*this);
            return cur;
        }

        list_iterator operator--(int) {
            list_iterator cur = *this;
            --(*this);
            return cur;
        }

        T& operator*() const {
            return static_cast<node*>(elem)->val;
        }

        T* operator->() const {
            return &static_cast<node*>(elem)->val;
        }

        bool operator==(const self_type& arg) const {
            return elem == arg.elem;
        }

        bool operator==(const list_const_iterator& arg) const {
            return list_const_iterator(elem) == arg;
        }

        bool operator!=(const self_type& arg) const {
            return !(*this == arg);
        }

        bool operator!=(const list_const_iterator& arg) const {
            return !(*this == arg);
        }

        operator list_const_iterator() const {
            return list_const_iterator(elem);
        }

        friend list;

    private:
        node_base* elem = nullptr;
    };

    node_base fake;

public:

    typedef list_iterator iterator;

    typedef list_const_iterator const_iterator;

    typedef std::reverse_iterator<iterator> reverse_iterator;

    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() {
        return iterator(fake.next);
    }

    const_iterator begin() const {
        return const_iterator(fake.next);
    }

    iterator end() {
        return iterator(&fake);
    }

    const_iterator end() const {
        return const_iterator(const_cast<node_base*>(&fake));
    }

    reverse_iterator rbegin() {
        return reverse_iterator(&fake);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(const_cast<node_base*>(&fake));
    }

    reverse_iterator rend() {
        return reverse_iterator(fake.next);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(fake.next);
    }

    list() noexcept = default;

    list(const list<T>& arg) : list() {
        for (const T& i : arg) {
            push_back(i);
        }
    }

    list<T>& operator=(const list<T>& arg) {
        if (this == &arg) {
            return *this;
        }
        list<T> cpy(arg);
        swap(cpy, (*this));
        return (*this);
    }

    ~list() {
        clear();
    }

    iterator insert(const_iterator pos, T const & arg) {
        node* elem = new node(arg);
        node_base* prev = pos.elem->prev;
        node_base* next = pos.elem;
        prev->next = elem;
        elem->prev = prev;
        next->prev = elem;
        elem->next = next;
        return iterator(elem);
    }

    iterator erase(const_iterator pos) {
        node_base* prev = pos.elem->prev;
        node_base* next = pos.elem->next;
        delete static_cast<node*>(pos.elem);
        prev->next = next;
        next->prev = prev;
        return iterator(next);
    }

    void push_back(T const & arg) {
        insert(end(), arg);
    }

    void pop_back() {
        erase(--end());
    }

    void push_front(T const & arg) {
        insert(begin(), arg);
    }

    void pop_front() {
        erase(begin());
    }

    T const & back() const noexcept {
        return static_cast<node*>(fake.prev)->val;
    }

    T& back() noexcept {
        return static_cast<node*>(fake.prev)->val;
    }

    T const & front() const noexcept {
        return static_cast<node*>(fake.next)->val;
    }

    T& front() noexcept {
        return static_cast<node*>(fake.next)->val;
    }

    bool empty() const {
        return (fake.next == &fake &&  fake.prev == &fake);
    }

    template <typename InputIterator>
    void splice(InputIterator pos, list<T> & arg, InputIterator first, InputIterator last) {
        if (first == last)
            return;
        node_base* beg = pos.elem->prev;
        node_base* cf = first.elem;
        node_base* cl = last.elem->prev;
        cf->prev->next = cl->next;
        cl->next->prev = cf->prev;
        beg->next = cf;
        cf->prev = beg;
        cl->next = pos.elem;
        pos.elem->prev = cl;
    }

    void clear() {
        while(!empty())
            pop_back();
    }

    template <typename U>
    friend void swap(list<U> & a, list<U> & b);
};

template <typename T>
void swap(list<T> &a, list<T> &b) {
    if (a.empty() && b.empty()) {
        a.fake.next = &b.fake;
        a.fake.prev = &b.fake;
        b.fake.next = &a.fake;
        b.fake.prev = &a.fake;
        std::swap(a.fake, b.fake);
        return;
    }
    if (a.empty() && !b.empty()) {
        a.fake.next = &b.fake;
        a.fake.prev = &b.fake;
        b.fake.next->prev = &a.fake;
        b.fake.prev->next = &a.fake;
        std::swap(a.fake, b.fake);
        return;
    }
    if (!a.empty() && b.empty()) {
        a.fake.next->prev = &b.fake;
        a.fake.prev->next = &b.fake;
        b.fake.next = &a.fake;
        b.fake.prev = &a.fake;
        std::swap(a.fake, b.fake);
        return;
    }
    if (!a.empty() && !b.empty()) {
        a.fake.next->prev = &b.fake;
        a.fake.prev->next = &b.fake;
        b.fake.next->prev = &a.fake;
        b.fake.prev->next = &a.fake;
        std::swap(a.fake, b.fake);
        return;
    }
    std::swap(a.fake, b.fake);
}


#endif //EXAM_LIST_LIST_H

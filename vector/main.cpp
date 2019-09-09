#include <iostream>
#include "vector.h"
#include <algorithm>
#include "counted.h"

struct elem {
    elem() = delete;

    int val;

    elem(int x) {
        val = x;
    }
};

void ujigajuga() {
    std::cout << '\n' << '\n' << '\n';
}

typedef vector<counted> container;

int main() {
    ujigajuga();

    container c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    container d;
    d.push_back(4);
    std::cout << d[0] << '\n';
    d.assign(c.begin(), c.end());
    /*std::cout << d.size() << ' ' << d[0] << ' ' << d[1] << ' ' << d[2] << '\n';
    container e;
    e.push_back(5);
    c.assign(e.begin(), e.end());
    std::cout << c.size() << ' ' << c[0];*/

    return 0;
}
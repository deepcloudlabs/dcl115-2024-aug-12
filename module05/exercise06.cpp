#include <iostream>
#include <thread>

using namespace std;

atomic<bool> x{false}; // Data
atomic<bool> y{false}; // Data

void fun1() {
    x.store(true);
}

void fun2() {
    while (!x.load());
    y.store(true);
}

void fun3() {
    while (!y.load());
    if (x.load()) {
        cerr << "x and y are all true!" << endl;
    } else {
        cerr << "y is true and x is false!" << endl;
    }
}

int main() {
    jthread t1{fun1};
    jthread t2{fun2};
    jthread t3{fun3};
    return 0;
}
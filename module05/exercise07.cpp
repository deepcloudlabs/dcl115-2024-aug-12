#include <iostream>
#include <thread>

using namespace std;

atomic<bool> x{false}; // Data
atomic<bool> y{false}; // Data
int state1 = 0;
int state2 = 0;
mutex m;

void fun1() {
    state1 = 42;
    atomic_thread_fence(memory_order_release);
    x.store(true, memory_order_release);
}

void fun2() {
    state2 = 108;
    atomic_thread_fence(memory_order_release);
    y.store(true, memory_order_release);
}

void gun1() {
    while (!x.load(memory_order_acquire));
    while (!y.load(memory_order_acquire));
    atomic_thread_fence(memory_order_acquire);
    {
        lock_guard<mutex> lg{m};
        cerr << "gun1: state1= " << state1
             << ", state2= " << state2
             << endl << flush;
    }
}

void gun2() {
    while (!x.load(memory_order_acquire));
    while (!y.load(memory_order_acquire));
    atomic_thread_fence(memory_order_acquire);
    {
        lock_guard<mutex> lg{m};
        cerr << "gun2: state1= " << state1
             << ", state2= " << state2
             << endl << flush;
    }
}


int main() {
    jthread t1{fun1};
    jthread t2{fun2};
    jthread t3{gun1};
    jthread t4{gun2};
    return 0;
}
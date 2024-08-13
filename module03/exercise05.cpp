#include <iostream>
#include <thread>

using namespace std;

struct A {
    int state;

    explicit A(int state) : state(state) {}

    A() {
        cerr << "Constructor is executed by the thread[" << dec << this_thread::get_id() << "]" << endl;
    }

    ~A() {
        cerr << "Destructor is executed by the thread[" << dec << this_thread::get_id() << "]" << endl;
    }

    void fun() {
        for (auto i = 0; i < 1'000'000; ++i) state++;
        cerr << "fun is executed by the thread[" << dec << this_thread::get_id() << "]: " << hex << &state << endl;
    }
};

thread_local A a;

void task() {
    a.fun();
}

int main() {
    {
        jthread t1{task};
        jthread t2{task};
        jthread t3{task};
    }
    cerr << "a.state: " << dec << a.state << "," << hex << &(a.state) << endl;
    return 0;
}
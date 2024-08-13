#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

using namespace std;

class singleton { // ts
    int state;
    mutex m;
public:
    void fun(){
        lock_guard<mutex> lock(m);
        state++;
    }
};

shared_ptr<singleton> singleton_ptr;
// lazy initialization
once_flag singleton_flag;

void instantiate_singleton() {
    singleton_ptr.reset(new singleton);
}

void task(){
    call_once(singleton_flag,instantiate_singleton);
    singleton_ptr->fun();
}

int main() {
    {
        jthread t1{task};
        jthread t2{task};
        jthread t3{task};
    }
    return 0;
}
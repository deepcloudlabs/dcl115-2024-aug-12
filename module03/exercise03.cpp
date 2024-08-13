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
mutex singleton_mutex;

void task(){
    { // critical section -> instantiating singleton
        unique_lock<mutex> lock(singleton_mutex);
        if (!singleton_ptr){
            singleton_ptr.reset(new singleton);
        }
    }
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
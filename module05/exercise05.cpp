#include <iostream>
#include <thread>
#include "utils.h"

using namespace std;

//global atomic variable
atomic<int> counter{0};

// global ordinary variable
int state = 0;

void fun() { // t1 -> cpu7
    bind_self_to_core(1);
    for (auto i = 0; i <= 100'000'000; ++i) {
        state = i;
        atomic_thread_fence(memory_order_release);
        counter.store(i);
    }
}


void gun() { // t2 -> cpu7
    bind_self_to_core(2);
    int prevValue = 0;
    while (prevValue < 100'000'000){
        while (true){
            auto newValue = counter.load();
            if (prevValue < newValue){
                prevValue = newValue;
                atomic_thread_fence(memory_order_acquire);
                cout << "state is " << state << ", newValue is " << newValue << endl << flush;
                break;
            }
        }
    }
}

int main() {
    jthread t1{fun};
    jthread t2{gun};
    this_thread::sleep_for(30s);
    return 0;
}
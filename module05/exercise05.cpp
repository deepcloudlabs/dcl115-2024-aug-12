#include <iostream>
#include <thread>

using namespace std;

//global atomic variable
atomic<int> counter{0};

// global ordinary variable
int state = 0;

void fun() { // t1 -> cpu4
    for (auto i = 0; i <= 1'000'000; ++i) {
        state = i;
        atomic_thread_fence(memory_order_release);
        counter.store(i);
    }
}


void gun() { // t2 -> cpu4
    int prevValue = 0;
    while (prevValue < 1'000'000){
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
    return 0;
}
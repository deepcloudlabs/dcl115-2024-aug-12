#include <iostream>
#include <thread>

using namespace std;

atomic<bool> flag{false};
int state = 0;

// producer
void fun(){ // t1 -> cpu0,1 (core) -> L1 (state)
    state = 42;
    atomic_thread_fence(memory_order_release);
    flag.store(true);
}
// consumer
void gun(){ // t2 -> cpu11,12 (core) -> L1 (state)
    while(!flag.load()); // t2 -> spinning
    atomic_thread_fence(memory_order_acquire);
    cerr << "state is " << state << endl;
}

int main(){
    // t1 -> write state -> synchronization{flag} -> read state -> processing
    jthread t1{fun};
    jthread t2{gun};
    return 0;
}
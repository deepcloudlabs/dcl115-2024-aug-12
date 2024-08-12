#include <iostream>
#include <thread>
#include <pthread.h>

using namespace std;

void task() {
    cerr << "thread id is " << this_thread::get_id() << endl;
    pthread_t current_thread = pthread_self();
    cerr << "pthread id is " << current_thread << endl;
}

int main() { // thread -> main()
    jthread t1{task}; // 2
    jthread t2{task}; // 3
    jthread t3{task}; // 4
    cerr << "thread id is " << this_thread::get_id() << endl;

    return 0;
}

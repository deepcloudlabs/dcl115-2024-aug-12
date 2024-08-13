#include <iostream>
#include <thread>
using namespace std;

int global_state = 0; // data
mutex m;

void fun(){
    cerr << "fun is started by the thread "
         << this_thread::get_id
         << "." << endl;
    for (auto i=0;i<1'000'000;++i){
        // critical section -> race
        // serial execution
        lock_guard<mutex> lock(m);
        global_state++;
    }
    cerr << "fun is returned by the thread "
         << this_thread::get_id
         << "." << endl;
}

int main() {
    cerr << "global_state: " << global_state << endl;
    {
        // all are mutator threads
        jthread t1{fun};
        jthread t2{fun};
        jthread t3{fun};
        jthread t4{fun};
        jthread t5{fun};
        jthread t6{fun};
        // lock contention
    }
    cerr << "global_state: " << global_state << endl;
    return 0;
}
// global_state: 1277961
// global_state: 1443769
// global_state: 1140694
#include <iostream>
#include <thread>
using namespace std;

thread_local int global_state = 0; // data
int x;

void fun(){
    cerr << "fun is started by the thread "
         << this_thread::get_id()
         << "." << endl;
    for (auto i=0;i<1'000'000;++i){
        // critical section -> race
        // serial execution
        global_state++;
    }

    cerr << "fun is returned by the thread "
         << this_thread::get_id()
         << ":"
         << global_state
         << endl;
}

int main() {
    int y;
    cerr << this_thread::get_id() << ", global_state: " << global_state << endl;
    {
        // all are mutator threads
        jthread t1{fun};
        jthread t2{fun};
        jthread t3{fun};
        jthread t4{fun};
        jthread t5{fun};
        jthread t6{fun};
        jthread t7{fun};
        jthread t8{fun};
        // lock contention
    }
    cerr << this_thread::get_id() << ", global_state: " << global_state << endl;
    cerr << "&x: " << hex << &x << endl;
    cerr << "&y: " << hex << &y << endl;
    cerr << "&global_state: " << hex << &global_state << endl;
    return 0;
}
// global_state: 1277961
// global_state: 1443769
// global_state: 1140694
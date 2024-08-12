#include <iostream>
#include <thread>

using namespace std;

void fun(int id){
    cerr << "task[" << id << "] is running..." << endl;
    this_thread::sleep_for(10s);
    cerr << "task[" << id << "] is now completed." << endl;
}

int gun(){ // async
    thread t1{fun,1};
    t1.detach();
    // if (t1.joinable()) //guard
        // t1.join();
    return 42;
}

int sun(){ // sync
    jthread t1{fun,1};
    cerr << "sun is running..." << endl;

    return 42;
}


int main() { // text
    cerr << "Application is just started: " << std::endl;
    cerr << "Result is " << gun() << endl;
    cerr << "Result is " << sun() << endl;
    this_thread::sleep_for(15s);
    cerr << "Application is just stopped." << std::endl;
    return 0;
}

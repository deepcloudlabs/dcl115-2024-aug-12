#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

bool flag = false;
mutex m;

void fun(){
    std::cout << "fun() is just started!" << std::endl;
    this_thread::sleep_for(8s);
    std::cout << "fun() is about to exit!" << std::endl;
    flag = true; // signaling other threads!
    std::cout << "fun() has exited!" << std::endl;
}

void wait_for(){ // thread-safe
    unique_lock<mutex> ul(m);
    while (flag == false){ // rendezvous
        ul.unlock();
        std::cout << "flag is false, we sleep 100ms..." << std::endl;
        this_thread::sleep_for(100ms);
        std::cout << "we are awake and check the flag..." << std::endl;
        ul.lock();
    }
}

void gun(){
    // t2 starts when t1 finishes
    std::cout << "thread[" << this_thread::get_id() << "] is waiting for the flag!" << std::endl;
    wait_for();
    std::cout << "gun() is just started!" << std::endl;
    this_thread::sleep_for(5s);
    std::cout << "gun() has exited!" << std::endl;
}

int main() {
    std::cout << "Application is just started!" << std::endl;
    {
        jthread t1{fun};
        jthread t2{gun};
        jthread t3{gun};
        jthread t4{gun};
    }
    return 0;
}

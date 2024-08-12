#include <iostream>
#include <thread>
#include <numeric>

using namespace std;

void gun() {
    cerr << "gun() is running ..." << endl;
    this_thread::sleep_for(3s);
}

void fun(thread t){
    cerr << "fun() is running ..." << endl;
    if (t.joinable()) t.join();
    //t.detach();
    cerr << "fun() is returning ..." << endl;
}
int main() {
    cerr << "Application is just started." << std::endl;
    thread t1{gun}; // initially joinable thread
    fun(move(t1));
    cerr << "Application is just stopped." << std::endl;
    return 0;
}

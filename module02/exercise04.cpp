#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void task(int id) {
    cerr << "task[" << id << "] is running ..." << endl;
    this_thread::sleep_for(100ms);
    cerr << "task[" << id << "] is returning..." << endl;
}

void fun() {
    vector<thread> threads;
    cerr << "fun() is running ..." << endl;
    for (auto i = 1; i <= 128; ++i) {
        threads.emplace_back((thread{task, i}));
    }
    for_each(threads.begin(),threads.end(),mem_fn(&thread::join));
    cerr << "fun() is returning ..." << endl;
}

int main() {
    cerr << "Application is just started." << std::endl;
    {
     jthread t{fun};
    }
    cerr << "Application is just stopped." << std::endl;
    return 0;
}

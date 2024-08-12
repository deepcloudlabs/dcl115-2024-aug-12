#include <iostream>
#include <thread>

using namespace std;

void fun(int id, int &data) {
    cout << "task[" << id << "] is running..." << endl;
    for (auto i = 0; i < 1'000'000; ++i) {
        data++;
    }
    cout << "task[" << id << "] is returning: " << data << endl;
}

int main() {
    cerr << "Application is just started: " << std::endl;
    cerr << "Number of logical processors: "
         << thread::hardware_concurrency()
         << endl;
    int x = 0; // stack
    {
        jthread t1{fun,1,ref(x)};
        jthread t2{fun,2,ref(x)};
        jthread t3{fun,3,ref(x)};
    }
    cerr << "Application is just stopped: " << x << std::endl;
    return 0;
}
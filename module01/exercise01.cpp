#include <iostream>
#include <thread>
using namespace std;

void fun() {}

void gun() {}

int x = 42;

void task1(int task_data){
    cout << "task1 is running and using task data: " << task_data << endl;
}

// Process -> Memory [text: main, fun, gun, data: x, y,  , stack: z,p , heap: *p, new/delete]
// Thread  -> Memory [                                     stack: ]
// 1. thread's task: global c-like function
int main() {
    int z = 108;
    static int y = 549;
    int *p = new int(42);
    std::cout << "Application is just started: " << *p << std::endl;
    delete p;
    // create the first thread
    thread t1{task1, 42}; // platform/kernel/os thread
    thread t2{task1, 108}; // platform/kernel/os thread
    // P -> cpu3, t1->cpu5, t2->cpu7
    // P -> cpu3, t1->cpu3, t2->cpu3
    // 1. io-bound, cpu-bound, mixed
    // 2. development/algorithm: t1 -> cpu5, cpu-binding
    // 3. cpu isolation -> kernel parameter -> cpu5, cpu17
    //    (2) t1 -> cpu binding -> cpu5
    //        t2 -> cpu binding -> cpu17
    //        ultra low latency
    t1.join();
    t2.join();
    std::cout << "Application is just stopped." << std::endl;
    return 0;
}

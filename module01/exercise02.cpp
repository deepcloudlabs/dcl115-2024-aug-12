#include <iostream>
#include <thread>
using namespace std;

void fun() {}

void gun() {}

int x = 42;

struct task {
    void operator()(int task_data){
        cout << "task1 is running and using task data: " << task_data << endl;
    }
};

int main() {
   std::cout << "Application is just started: " << std::endl;
    // create the first thread
    task task1{};
    thread t1{task1, 42};
    thread t2{task1, 108};
    thread t3{task(), 549};
    t1.join();
    t2.join();
    t3.join();
    std::cout << "Application is just stopped." << std::endl;
    return 0;
}

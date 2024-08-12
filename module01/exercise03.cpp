#include <iostream>
#include <thread>

using namespace std;

struct anonymous {
    void operator()(int task_data) {
        cout << "task is running and using task data: " << task_data << endl;
    }
};

// 3. thread's task: lambda expression -> functor
int main() {
    std::cout << "Application is just started: " << std::endl;
    // create the first thread
    thread t1{[](int task_data) {
        cout << "task is running and using task data: " << task_data << endl;
    }, 42};
    thread t2{[](int task_data) {
        cout << "task is running and using task data: " << task_data << endl;
    }, 108};
    thread t3{[](int task_data) {
        cout << "task is running and using task data: " << task_data << endl;
    }, 549};
    t1.join();
    t2.join();
    t3.join();
    std::cout << "Application is just stopped." << std::endl;
    return 0;
}

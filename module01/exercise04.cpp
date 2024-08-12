#include <iostream>
#include <thread>

using namespace std;

struct task {
    explicit task(int to_state) : state(to_state) {} // text

    void operator()(int task_id) { // text
        cout << "task[" << task_id << "] is running..." << endl;
        for (auto i=0;i<100'000;++i){
            this->state++;
        }
        cout << "task[" << task_id << "] is returning: " << this->state << endl;
    }

    int get_state() const { // text
        return state;
    }
private:
    int state;
};

// 2. thread's task: functor: struct + operator()

int main() { // text
    std::cout << "Application is just started: " << std::endl;
    // create the first thread
    task task1{0}; // stack object -> operator()
    thread t1{task1, 1}; // t1's stack copy
    thread t2{task1, 2}; // t2's stack copy
    thread t3{task1, 3}; // t3's stack copy
    t1.join();
    t2.join();
    t3.join();
    std::cout << "Application is just stopped: " << task1.get_state() << std::endl;
    return 0;
}

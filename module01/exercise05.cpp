#include <iostream>
#include <thread>

using namespace std;

int state = 0; // global variable -> data

void task(int task_id) { // c-like function -> text
    // task_id -> t{1,2,3}'s stack
    cerr << "task[" << dec << task_id << "," << hex << &task_id << "] is running..." << endl;
    for (auto i = 0; i < 1'000'000; ++i) {
        state++;
    }
    cerr << "task[" << dec << task_id << "] is returning: " << dec << state << "," << hex << &state << endl;
}

// Process -> Memory [text: main, fun, gun, data: x, y,  , stack: z,p , heap: *p, new/delete]
// Thread  -> Memory [                                     stack: ]
// stack size: 8M
// 1024 thread -> 1k * 8m = 8g -> virtual memory
// ulimit -s 1024
/*
 ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 256539
max locked memory       (kbytes, -l) 65536
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 256539
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
 */
// 1. thread's task: global c-like function
int main() {
    std::cerr << "Application is just started: " << dec << state << "," << hex << &state << std::endl;
    // create three threads
    thread t1{task, 1}; // platform/kernel/os thread
    thread t2{task, 2}; // platform/kernel/os thread
    thread t3{task, 3}; // platform/kernel/os thread
    t1.join();
    t2.join();
    t3.join();
    std::cerr << "Application is just stopped: " << dec << state << std::endl;
    return 0;
}

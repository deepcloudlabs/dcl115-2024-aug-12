#define _GNU_SOURCE
#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sched.h>
using namespace std;

#ifndef MODULE05_UTILS_H
#define MODULE05_UTILS_H
const int cpus = thread::hardware_concurrency();

int bind_self_to_core(int core_id) { // [0-11]
    core_id = core_id % cpus;
    cpu_set_t cpuset;
    // 0000 0000 0000
    CPU_ZERO(&cpuset);
    // if core_id is 7
    // 0000 1000 0000
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}
#endif //MODULE05_UTILS_H

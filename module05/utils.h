#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sched.h>
#define _GNU_SOURCE
using namespace std;

#ifndef MODULE05_UTILS_H
#define MODULE05_UTILS_H
const int cpus = thread::hardware_concurrency();

int bind_self_to_core(int core_id) {
    core_id = core_id % cpus;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}


template<typename Iterator, typename T>
void my_partial_sum(Iterator first, Iterator last, T &result) {
    static int cpu_id = 0;
    bind_self_to_core(cpu_id);
    cpu_id = (cpu_id + 1) % cpus;
    result = accumulate(first, last, result);
}
#endif //MODULE05_UTILS_H

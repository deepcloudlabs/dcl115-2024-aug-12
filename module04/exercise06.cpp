#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <functional>

using namespace std;

// 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
vector<long> fun(long n) {
    cerr << "thread[" << this_thread::get_id() << "] is running fun(" << n << ") now..." << endl;
    vector<long> result;
    result.push_back(n);
    while (n > 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        result.push_back(n);
    }
    return result;
}


int main() {
    std::cout << "Application is just started!" << std::endl;
    cerr << "thread[" << this_thread::get_id() << "] is calling async(...) now..." << endl;
    auto fun549 = bind(fun,549);
    packaged_task<vector<long>()> async_task{fun549};
    async_task();
    for (auto &number: async_task.get_future().get())
        cout << number << " ";
    cout << endl;
    return 0;
}

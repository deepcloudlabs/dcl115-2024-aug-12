#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
vector<long> list_numbers;

// 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
void fun(long n) {
//    vector<long> result;
    list_numbers.push_back(n);
    while (n > 1) {
          n = (n%2 == 0) ? n/2 : 3*n+1;
        list_numbers.push_back(n);
    }
}


int main() {
    std::cout << "Application is just started!" << std::endl;
    thread t1 {fun, 17};
    t1.join();
    for (auto& number : list_numbers)
        cout << number << " ";
    cout << endl;
    return 0;
}

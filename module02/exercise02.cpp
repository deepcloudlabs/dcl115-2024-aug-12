#include <iostream>
#include <thread>
#include <numeric>

using namespace std;

void fun(int &result, int *begin, int *end) {
    result = accumulate(begin, end, 0, [](int x, int y) { return x + y; });
}

int solution = 0;

int main() { // thread -> main()
    {
        int data[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int *p = data;
        int *q = data + 10;
        jthread t1{fun, ref(solution), p, q};
    }
    cerr << "solution is " << solution << endl;
    return 0;
}

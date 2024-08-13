#include <iostream>
#include <thread>
using namespace std;

struct task {
    explicit task(atomic<int>& state) : state(state) {}

    void operator()() {
        for (auto i = 0; i < 1'000'000; ++i)
            state++;
        cerr << "state: " << state << endl;
    }

private:
    atomic<int> &state;
};

int main() {
    atomic<int> local_state = 0;
    task task1{local_state};
    {
        jthread t1{task1};
        jthread t2{task1};
        jthread t3{task1};
    }
    cerr << "final value for local_state: " << local_state << endl;
    return 0;
}

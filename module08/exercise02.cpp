#include <iostream>
#include <vector>
#include <list>
#include <future>
#include <algorithm>

using namespace std;

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
    unsigned long const length = distance(first, last);

    if (length == 0) return;

    unsigned long const min_per_thread = 25;

    if (length < (2 * min_per_thread)) {
        for_each(first, last, f); // STL
    } else {
        Iterator const mid_point = first + length / 2;
        future<void> first_half =
                async(&parallel_for_each<Iterator, Func>,
                      first, mid_point, f);
        parallel_for_each(mid_point, last, f);
        first_half.get();
    }
}

int main() {
    vector<int> numbers;
    int i = 0;
    while (++i <= 3'000)
        numbers.push_back(i);
    parallel_for_each(numbers.begin(), numbers.end(), [](int i) { if (i % 11 == 0) cout << i << " " << flush; });
    return 0;
}
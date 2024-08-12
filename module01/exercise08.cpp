#include <iostream>
#include <thread>

using namespace std;

int main(){
    cerr << "Application is just started: " << std::endl;
    cerr << "Number of logical processors: "
         << thread::hardware_concurrency()
         << endl;
    cerr << "Application is just stopped: " << std::endl;
    return 0;
}
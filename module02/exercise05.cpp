#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void task1(int x,int y){

}
void task2(int* arr,int size){

}
void task3(int &sum,const int* arr,int size){

}
void task4(const int &sum,const int* arr,int size){

}
int main() {
    int my_array[]{1,2,3,4,5};
    int my_result;
    cerr << "Application is just started." << std::endl;
    {
     jthread t1{task1,3,5};
     jthread t2{task2,my_array,5};
     jthread t3{task3,ref(my_result),my_array,5};
     jthread t4{task4,cref(my_result),my_array,5};
    }
    cerr << "Application is just stopped." << std::endl;
    return 0;
}

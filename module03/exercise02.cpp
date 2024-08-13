#include <iostream>
#include <thread>
using namespace std;

class vehicle {
    const double capacity;
    double current_load;
public:
    explicit vehicle(const double capacity) : capacity(capacity) {
        this->current_load = 0;
    }

    double get_capacity() const {
        return this->capacity;
    }

    double get_current_load() const {
        return this->current_load;
    }

    double load(double weight) {
        if (weight <= 0.0) return this->current_load;
        if (weight + this->current_load > this->capacity) return this->current_load;
        this->current_load += weight;
        return this->current_load;
    }

    double unload(double weight) {
        if (weight <= 0.0) return this->current_load;
        if (weight > this->current_load) return this->current_load;
        this->current_load -= weight;
        return this->current_load;
    }
};

void transfer_task(vehicle& vehicle1, vehicle& vehicle2){
    for (int i=0;i<1'000'000;++i){
        vehicle1.unload(1);
        vehicle2.load(1);
    }
}
ostream& operator<<(ostream& os,vehicle& v){
    os << "vehicle[ current_load: " << v.get_current_load()
       << ", capacity: "
       << v.get_capacity()
       << " ]";
    return os;
}
vehicle vehicle1{100'000'000};
vehicle vehicle2{200'000'000};

int main(){
    vehicle1.load(100'000'000);
    {
        jthread t1{transfer_task,ref(vehicle1),ref(vehicle2)};
        jthread t2{transfer_task,ref(vehicle1),ref(vehicle2)};
        jthread t3{transfer_task,ref(vehicle1),ref(vehicle2)};
    }
    cerr << vehicle1 << endl;
    cerr << vehicle2 << endl;
    return 0;
}
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// immutable class
class point { // ts
    const int x, y;
public:
    point(int x, int y) : x(x), y(y) {}

    int get_x() const {
        return this->x;
    }

    int get_y() const {
        return this->y;
    }

    void draw() const {
        cerr << "drawing the point" << endl;
    }
};

// mutable class
class vehicle { // ts
    const double capacity; // immutable state
    double current_load;
    mutex m;
public:
    explicit vehicle(const double capacity) : capacity(capacity) {
        this->current_load = 0;
    }

    double get_capacity() const {
        return this->capacity;
    }

    double get_current_load() {
        lock_guard<mutex> lock{m};
        return this->current_load;
    }

    double load(double weight) {
        lock_guard<mutex> lock{m};
        if (weight <= 0.0) return this->current_load;
        if (weight + this->current_load > this->capacity) return this->current_load;
        this->current_load += weight;
        return this->current_load;
    }

    double unload(double weight) {
        lock_guard<mutex> lock{m};
        if (weight <= 0.0) return this->current_load;
        if (weight > this->current_load) return this->current_load;
        this->current_load -= weight;
        return this->current_load;
    }

    friend void transfer_load(vehicle &from_vehicle, vehicle &to_vehicle, double weight);
};

void transfer_load(vehicle &from_vehicle, vehicle &to_vehicle, double weight) {
    { // atomic
        unique_lock<mutex> lock1{from_vehicle.m, defer_lock};
        unique_lock<mutex> lock2{to_vehicle.m, defer_lock};
        lock(lock1, lock2);
        from_vehicle.unload(weight);
        to_vehicle.load(weight);
    }
    // doing something else

}

void transfer_task(vehicle &vehicle1, vehicle &vehicle2) {
    for (int i = 0; i < 1'000'000; ++i) {
        transfer_load(vehicle1, vehicle2, 1); // atomic
    }
}

ostream &operator<<(ostream &os, vehicle &v) {
    os << "vehicle[ current_load: " << v.get_current_load()
       << ", capacity: "
       << v.get_capacity()
       << " ]";
    return os;
}

vehicle vehicle1{100'000'000};
vehicle vehicle2{200'000'000};

int main() {
    vehicle1.load(100'000'000);
    {
        jthread t1{transfer_task, ref(vehicle1), ref(vehicle2)};
        jthread t2{transfer_task, ref(vehicle1), ref(vehicle2)};
        jthread t3{transfer_task, ref(vehicle1), ref(vehicle2)};
    }
    cerr << vehicle1 << endl;
    cerr << vehicle2 << endl;
    return 0;
}
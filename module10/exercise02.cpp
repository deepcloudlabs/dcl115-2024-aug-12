#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

#include "world-util.h"
std::map<int,std::shared_ptr<world::city>> cities;
std::map<std::string,std::shared_ptr<world::country>> countries;

int main() {
    create_world();
    set<string> continents;
    // external loop -> not easy to solve in parallel
    // imperative
    continents = accumulate(countries.begin(),countries.end(),set<string>(),[](auto continents,auto& country_pair) -> set<string>{
        continents.insert(country_pair.second->continent);
        return continents;
    });
    for (auto &continent: continents) {
       cout << continent << endl;
    }
    return 0;
}

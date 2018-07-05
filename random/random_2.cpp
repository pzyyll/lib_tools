#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "random_tools.h"

using namespace std;

void Random2(const int argc) {
    cout << "Random2" << endl;
    std::set<int> vals{1,3,4,5,6,7};
    std::vector<double> ws{5,1,1,1,1,1};

    std::map<int, int> imapcnt;

    for (unsigned i = 0; i < 10000; ++i) {

        auto res = lib_tools::Random::RandomSample(vals, ws, argc);
        for (auto itr : res) {
            //cout << itr << "|";
            imapcnt[itr] += 1;
        }
        //cout << endl;

    }

    for (auto itr : imapcnt) {
        cout << itr.first << "|" << itr.second << endl;
    }
}

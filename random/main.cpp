#include <iostream>
#include <map>
#include <set>

#include "random_tools.h"

using namespace std;
using namespace lib_tools;

int main(int argc, char **argv) {
    std::set<int> vals{1,3,4,5,6,7};
    std::vector<double> ws{5,1,1,1,1,1};

    std::map<int, int> imapcnt;

    for (unsigned i = 0; i < 10000; ++i) {

        auto res = Random::RandomSample(vals, ws, argc);
        for (auto itr : res) {
            //cout << itr << "|";
            imapcnt[itr] += 1;
        }
        //cout << endl;

    }

    for (auto itr : imapcnt) {
        cout << itr.first << "|" << itr.second << endl;
    }

    cout << "end" << endl;
    return 0;
}

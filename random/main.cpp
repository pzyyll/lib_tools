#include <iostream>
#include <map>

#include "random_tools.h"

using namespace std;
using namespace lib_tools;

int main() {
    std::vector<int> vals{1,3,9,4,5,6};
    std::vector<double> ws{5,1,1,1,1,1};

    std::map<int, int> imapcnt;

    for (unsigned i = 0; i < 10000; ++i) {

        auto res = Random::RandomSample(vals, ws, 6);
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

#include <iostream>
#include <map>
#include <set>

#include "random_tools.h"

using namespace std;
using namespace lib_tools;

int main(int argc, char **argv) {
    std::set<int> vals{1,2,5,25};
    std::vector<double> ws{76500,15300,10200,1};

    std::map<int, int> imapcnt;

    for (unsigned i = 0; i < 1000000; ++i) {

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


    std::vector<int> weights{5,5};
    unsigned resi = Random::DiscreteDist(weights.begin(), weights.end());
    cout << resi << endl;

    cout << "end" << endl;
    return 0;
}

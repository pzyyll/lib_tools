#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <array>

#include "utility_tools.h"

using namespace std;
using namespace lib_tools;

int main(int argc, char **argv) {

    vector<int> test_nums{0, 10, 20, 30, 50, 60, 100};

    cout << IndexLowerBound(test_nums.begin(), test_nums.end(), 10) << endl;
    cout << IndexLowerBoundRightOpen(test_nums.begin(), test_nums.end(), 10) << endl;

    array<int, 10> arr10 = {1};

    arr10.
    for (unsigned i = 0; i < arr10.size(); ++i) {
        cout << arr10[i] << endl;
    }

    cout << "end" << endl;
    return 0;
}

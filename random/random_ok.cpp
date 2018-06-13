#include <iostream>

#include "random_tools.h"

using namespace std;
using namespace lib_tools;

int main() {

    unsigned cnt = 0;
    unsigned all = 100000;
    for (unsigned i = 0; i < all; ++i) {
        if (Random::BernoulliDist(1))
            ++cnt;
    }

    cout << cnt << "/" << all << endl;

    return 0;
}

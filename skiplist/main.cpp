#include <iostream>
#include <string>

#include "skiplist.h"

using namespace std;
using namespace lib_tools;

SkipList<string> sl;

int main() {
    sl.Insert(1, "czl");
    sl.Insert(2, "zs");
    sl.Insert(2, "hao");
    sl.Insert(4, "lis");

    for (auto itr = sl.being(); itr != sl.end(); ++itr) {
        cout << itr->score << ":";
        cout << itr->data.val << endl;
    }

    cout << sl.GetRank(2, "hao") << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
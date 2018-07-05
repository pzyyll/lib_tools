#include <iostream>
#include <string>
#include <map>
#include <type_traits>
#include <memory>

#include "skiplist.h"

using namespace std;

typedef shared_ptr<int> IntPtr;

struct LessCmp {
    bool operator()(const IntPtr &a, const IntPtr &b) {
        return *a > *b;
    }
};

void TestConst() {
    typedef lib_tools::SkipList<IntPtr, int, LessCmp> RankType;
    RankType skiplist;


    skiplist.Insert(make_shared<int>(3), 3);
    skiplist.Insert(make_shared<int>(2), 2);

    const RankType &csk = skiplist;

    for (const RankType::val_type &itr : skiplist) {
        cout << itr.second << endl;
    }

    RankType::const_pointer cp = &(*skiplist.begin());

    cout << csk.begin()->second << endl;
}

int main() {
    TestConst();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

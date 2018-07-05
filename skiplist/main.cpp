#include <iostream>
#include <string>
#include <map>
#include <type_traits>
#include <memory>

#include "skiplist.h"

using namespace std;

typedef shared_ptr<int> IntPtr;

struct LessCmp {
    bool operator()(const IntPtr &a, const IntPtr &b) const {
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

class Test {
public:
    void Init() {
        skiplist.Insert(make_shared<int>(3), 3);
        skiplist.Insert(make_shared<int>(2), 2);
    }
    void P() const {
        for (auto itr : skiplist) {
            cout << itr.second << endl;
        }
    }
private:
    typedef lib_tools::SkipList<IntPtr, int, LessCmp> RankType;
    RankType skiplist;
};

int main() {
    //TestConst();

    Test test;
    test.Init();
    const Test &const_test = test;

    const_test.P();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

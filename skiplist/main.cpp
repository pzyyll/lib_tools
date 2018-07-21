#include <iostream>
#include <string>
#include <map>
#include <type_traits>
#include <memory>

#include "skiplist.h"
#include "ranklist_v1.h"

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
    struct ScoreInfo {
        ScoreInfo() : lid(0), score(0), name("") {}

        bool operator<(const ScoreInfo &info) const {
            return score > info.score;
        }

        int lid;
        int score;
        std::string name;
    };
public:
    void Init() {
        ScoreInfo a, b;
        a.lid = 1001; a.score = ascore = 1; a.name = "a";
        b.lid = 1002; b.score = bscore = 1; b.name = "b";

        skiplist.Insert(a, a.lid);
        skiplist.Insert(b, b.lid);
    }

    void Up() {
        ScoreInfo a, b;
        a.lid = 1001; a.score = (ascore += random() % bscore); a.name = "a";
        b.lid = 1002; b.score = (bscore += random() % ascore); b.name = "b";

        skiplist.Update(b, b.lid);
        skiplist.Update(a, a.lid);

        P();
    }

    void P() const {
        for (auto itr : skiplist) {
            cout << itr.second << "|" << itr.first.name << "|" << itr.first.score << "|" << itr.first.lid << endl;
        }
    }
private:
    typedef lib_tools::RankList<ScoreInfo, int> RankType;
    RankType skiplist;

    int ascore;
    int bscore;
};

int main() {
    //TestConst();

    Test test;
    test.Init();
    //const Test &const_test = test;

    test.P();

    for (unsigned i = 0; i < 100; ++i) {
        cout << "begin" << endl;
        test.Up();
        cout << "end" << endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

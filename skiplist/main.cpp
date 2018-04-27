#include <iostream>
#include <string>
#include <map>
#include <type_traits>

#include "skiplist.h"

using namespace std;
using namespace lib_tools;

struct Key {
    Key() : val(0), id(0) { }
    Key(const int v, const int i) : val(v), id(i) { }
    bool operator<(const Key &k) const {
        if (val != k.val)
            return val > k.val;
        return id < k.id;
    }

    bool operator==(const Key &k) const {
        if (val != k.val)
            return false;
        return id == k.id;
    }

    int val;
    int id;
};

SkipList<double, string> sl;

map<int, int> ii_map;
int main() {
    sl.Insert(1, "czl");
    sl.Insert(2, "zs");
    sl.Insert(2, "hao");
    sl.Insert(4, "lis");

    for (auto itr = sl.begin(); itr != sl.end(); ++itr) {
        cout << itr->first << ":";
        cout << itr->second << endl;
    }

    cout << sl.GetRank(2, "hao") << endl;
    cout << sl.FirstInRangeByRank(Range(1,2))->second << endl;

    struct TLess {
        int val;
        int id;
    };
    TLess a{1,2}, b{3,4};
    //cout << less1(a,b) << endl;

    Key k1{1,2};
    Key k2{1,1};
    Key k3{1,4};
    Key k4{3,3};
    Key k5{2,2};

    SkipList<Key, string> ks;
    ks.Insert(k1, "k1");
    ks.Insert(k2, "k2");
    ks.Insert(k3, "k3");
    ks.Insert(k4, "k4");
    ks.Insert(k5, "k5");

    cout << ks.FirstInRangeByRank(Range(2,2))->second << endl;
    cout << ks.GetRank(Key(1,2), "czlh") << endl;

    for (auto itr = ks.begin(); itr != ks.end(); ++itr)
    {
        cout << itr->first.val << " : " << itr->first.id << " ";
        cout << itr->second << endl;
    }

    ks.Delete(k3, "k3");
    ks.Delete(ks.last());
    ks.Delete(ks.last());
    cout << "-----ks delete k3" << endl;

    for (auto itr = ks.begin(); itr != ks.end(); ++itr)
    {
        cout << itr->first.val << " : " << itr->first.id << " ";
        cout << itr->second << endl;
    }

    cout << "ks lenth : " << ks.Lenth() << endl;
    std::cout << "----------------" << std::endl;

    SkipList<Key, int> sl_ki;
    sl_ki.Insert(k1, k1.id);
    sl_ki.Insert(k2, k2.id);
    for (auto itr = sl_ki.begin(); itr != sl_ki.end(); ++itr)
    {
        std::cout << itr->first.val << " : ";
        std::cout << itr->second << endl;
    }

    for (auto itr : sl_ki)
    {
        cout << itr.second << endl;
    }

    cout << "--- clear ----" << endl;
    sl_ki.Clear();

    cout << sl_ki.Lenth() << std::endl;
    cout << "--- clear aft insert ---" << endl;
    sl_ki.Insert(k1, k1.id);

    for (auto itr = sl_ki.begin(); itr != sl_ki.end(); ++itr)
    {
        std::cout << itr->first.val << " : ";
        std::cout << itr->second << endl;
    }

    cout << "lenth " << sl_ki.Lenth() << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

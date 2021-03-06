//
// Created by czl17 on 2018-3-30.
//

#include <iostream>
#include <cstdlib>
#include "ranklist_v1.h"
#include <functional>
#include <map>
#include <memory>

using namespace std;

struct Key {
    Key() : val(-1), id(-1), online(false) { }
    Key(const int v, const int i) : val(v), id(i), online(false) { }

    /*
    bool operator< (const Key &k) const {
        if (val != k.val)
            return val > k.val;
        return id < k.id;
    }
    */
    void Detail() const {
        std::cout << "id: " << id << ", val: " << val << ", online: " << online << endl;
    }

    int val;
    int id;
    bool online;
};

struct KeyLess {
    bool operator()(const Key &key1, const Key &key2) const {
        if (key1.online != key2.online)
            return key1.online > key2.online;
        if (key1.val != key2.val)
            return key1.val > key2.val;
        return key1.id < key2.id;
    }
};

void TestFunc() {
    lib_tools::RankList<Key, int, KeyLess> rank_list(30);

    //Insert func
    for (int i = 1; i < 30; ++i) {
        Key k(rand()%5, i);
        rank_list.Insert(k, i);
    }

    auto up1 = rank_list.GetByData(1);
    Key newf = up1->first;
    newf.online = true;

    rank_list.Update(newf, newf.id);

    auto up2 = rank_list.GetByData(7);
    newf = up2->first;
    newf.online = true;

    rank_list.Update(newf, newf.id);

    //Range-for at ranklist
    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : ";
        itr.first.Detail();
    }

    //Delete by data-identify
    rank_list.Delete(15);

    //Updata func
    std::cout << "---update---" << std::endl;
    rank_list.Update(Key(15, 7), 7);
    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : ";
        itr.first.Detail();
    }

    //Get rank-posion by data-identify
    std::cout << rank_list.GetRank(1) << std::endl;
    std::cout << rank_list.GetRank(2) << std::endl;

    //Get the top rank posion info iterator
    std::cout << "----" << std::endl;
    auto begin_itr = rank_list.GetTopRank(8);
    for (int i = 0; i < 4 && begin_itr != rank_list.end(); ++i,++begin_itr)
    {
        std::cout << "id : " << begin_itr->second << std::endl;
        std::cout << "key_info : ";
        begin_itr->first.Detail();
    }

    std::cout << rank_list.GetSize() << std::endl;

    std::cout << "----GetByData----" << std::endl;
    auto fitr = rank_list.GetByData(7);
    if (fitr == rank_list.end())
        std::cout << "no find" << std::endl;

    std::cout << "id : " << fitr->second << std::endl;
    std::cout << "key_info : ";
    fitr->first.Detail();

    std::cout << "end" << std::endl;

    std::cout << "----" << std::endl;

    std::cout << "---test2---" << std::endl;
    lib_tools::RankList<int, int> iiranklist;
    iiranklist.Insert(1,1);
    iiranklist.Insert(1,2);
    iiranklist.Insert(2,3);
    iiranklist.Update(22,2);

    for (auto &itr : iiranklist) {
        std::cout << "key: " << itr.first << ", val: " << itr.second << std::endl;
    }

    auto iifitr = iiranklist.GetByData(2);
    std::cout << iifitr->first << "|" << iifitr->second << std::endl;
    std::map<int, int> iimap;

    shared_ptr<int> ipointer = make_shared<int>(12);

    *ipointer = 2;

    cout << *ipointer << endl;


    cout << "--- clear ---" << endl;
    rank_list.Clear();
    cout << "clear aft size : " << rank_list.GetSize() << endl;
    cout << "is empty : " << rank_list.Empty() << endl;

    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : ";
        itr.first.Detail();
    }

    rank_list.Insert(Key(15, 7), 7);
    cout << "clear aft size : " << rank_list.GetSize() << endl;
    cout << "is empty : " << rank_list.Empty() << endl;

    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : ";
        itr.first.Detail();
    }
}

namespace test_range {


struct Key {

    Key(const int sc = 0, const int t = 0) : score(sc), tm(t) {  }
    ~Key() = default;

    bool operator<(const Key &k) const {
        if (score != k.score)
            return score < k.score;
        return tm < k.tm;
    }

    int score;
    int tm;
};

typedef lib_tools::RankList<Key, int> RankType;
RankType kRanklist;

void Print(const RankType &ranklist) {
    for (RankType::val_type itr : ranklist) {
        cout << "Key: " << itr.first.score << "|" << itr.first.tm <<
            ", id: " << itr.second << endl;
    }
}

void Print(RankType::iterator b, RankType::iterator e) {
    while (b != e) {
        cout << "Key: " << (*b).first.score << "|" << (*b).first.tm <<
                ", id: " << (*b).second << endl;
        ++b;
    }
    cout << "Key: " << (*b).first.score << "|" << (*b).first.tm <<
        ", id: " << (*b).second << endl;
}

void Test() {
    kRanklist.Insert(Key(1, 0), 1);
    kRanklist.Insert(Key(10, 0), 2);
    kRanklist.Insert(Key(2, 0), 3);
    kRanklist.Insert(Key(5, 0), 4);
    kRanklist.Insert(Key(2, 0), 5);

    Print(kRanklist);

    auto bitr = kRanklist.GetFirstInRangeByScore(Key(2, 0), Key(12, 0));
    auto eitr = kRanklist.GetLastInRangeByScore(Key(2, 0), Key(12, 0));

    cout << "Test" << endl;

    Print(bitr, eitr);

    RankType::val_type val = *kRanklist.begin();
    cout << val.first.score << endl;
    cout << val.second << endl;

    auto itr = kRanklist.GetByData(2);
    cout << itr->second << endl;

    cout << "End Test." << endl;
}

}


struct KeyTest {

    bool operator == (const KeyTest k) const {
        return i == k.i;
    }

    int i;
};

int main() {
    //TestFunc();
    //test_range::Test();

    lib_tools::RankList<unsigned, unsigned, std::greater<unsigned>> rank_list;

    rank_list.Update(1,1);
    rank_list.Update(2,2);

    for (auto itr : rank_list) {
        cout << itr.first << itr.second << endl;
    }

    return 0;
}

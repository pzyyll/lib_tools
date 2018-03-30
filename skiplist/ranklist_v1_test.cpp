//
// Created by czl17 on 2018-3-30.
//

#include <iostream>
#include <cstdlib>
#include "ranklist_v1.h"

struct Key {
    Key() : val(-1), id(-1) { }
    Key(const int v, const int i) : val(v), id(i) { }

    bool operator< (const Key &k) const {
        if (val != k.val)
            return val > k.val;
        return id < k.id;
    }

    bool operator== (const Key &k) const {
        if (val != k.val)
            return false;
        return id == k.id;
    }

    int val;
    int id;
};

int main() {
    lib_tools::RankList<Key> rank_list(10);

    //Insert func
    for (int i = 1; i < 20; ++i) {
        Key k(rand()%5, i);
        rank_list.Insert(k, i);
    }

    //Range-for at ranklist
    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : " << itr.first.val << "|" << itr.first.id << std::endl;
    }

    //Delete by data-identify
    rank_list.Delete(15);

    //Updata func
    std::cout << "---update---" << std::endl;
    rank_list.Update(Key(15, 7), 7);
    for (auto itr : rank_list)
    {
        std::cout << "id : " << itr.second << std::endl;
        std::cout << "key_info : " << itr.first.val << "|" << itr.first.id << std::endl;
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
        std::cout << "key_info : " << begin_itr->first.val << "|" << begin_itr->first.id << std::endl;
    }

    return 0;
}

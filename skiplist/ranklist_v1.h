//
// Created by czl17 on 2018-3-30.
//

#ifndef SKIPLIST_RANKLIST_V1_H
#define SKIPLIST_RANKLIST_V1_H

#include <unordered_map>
#include "skiplist.h"

namespace lib_tools {

    template<typename Key, typename Data = int, typename DefaultCmp = DefaultValCmp<Data>>
    class RankList {
    public:
        typedef SkipList<Key, Data, DefaultCmp> SkipListType;
        typedef typename SkipListType::iterator iterator;

        RankList(const unsigned max_size) : _max_size(max_size) { }

        bool Insert(Key key, Data identify) {
            if (_key_map.find(identify) != _key_map.end())
                return false;
            if (!_key_map.insert(std::make_pair(identify, key)).second)
                return false;
            _rank_list.Insert(key, identify);

            if (_rank_list.Lenth() > _max_size) {
                auto lastitr = _rank_list.last();
                _key_map.erase(lastitr->second);
                _rank_list.Delete(lastitr);
            }

            return true;
        }

        void Delete(Data identify) {
            auto itr = _key_map.find(identify);
            if (_key_map.end() == itr)
                return;
            _rank_list.Delete(itr->second, itr->first);
            _key_map.erase(itr);
        }

        bool Update(Key key, Data identify) {
            auto finditr = _key_map.find(identify);

            if (finditr == _key_map.end())
                return Insert(key, identify);

            _rank_list.Delete(finditr->second, finditr->first);
            _rank_list.Insert(key, identify);
            finditr->second = key;
        }

        unsigned long GetRank(Data identify) {
            auto itr = _key_map.find(identify);
            if (itr == _key_map.end())
                return 0;
            return _rank_list.GetRank(itr->second, itr->first);
        }

        iterator GetTopRank(const unsigned long rank) {
            if (rank > _rank_list.Lenth())
                return _rank_list.end();
            return _rank_list.FirstInRangeByRank(lib_tools::Range(rank, rank));
        }

        iterator begin() { return _rank_list.begin(); }
        iterator end() { return _rank_list.end(); }
        iterator last() { return _rank_list.last(); }

    private:
        lib_tools::SkipList<Key, Data> _rank_list;
        std::unordered_map<Data, Key> _key_map;

        unsigned _max_size;
    };
} //namespace ranklist

#endif //SKIPLIST_RANKLIST_V1_H

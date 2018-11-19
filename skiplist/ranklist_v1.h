// ranklist_v1.h
// @Created by czl17 on 2018-3-30.
// @brief ranklist implement by skiplist with hashtable
// Key             存储 key 值，例如分数值等，可重复，可自定义结构，需提供默认小于比较
// Data            存储用户数据，可用于唯一识别标志, 自定义结构需要提供 hash 函数, 等于比较
// DataCompare      Data 小于比较算法
//
// func Insert     插入一个键值对, 存在则插入失败
// func Delete     删除用户数据
// func Update     更新一个键值对, 无则插入
// func GetSize    元素个数
// func GetRank    获取用户数据排行位置
// func GetByData  通过用户数据获取存储的元素, 返回迭代器
// func GetTopRank 返回排行第 top 的元素迭代器


#ifndef SKIPLIST_RANKLIST_V1_H
#define SKIPLIST_RANKLIST_V1_H

#include <unordered_map>
#include <map>
#include "skiplist.h"

namespace lib_tools {

template<typename Key, typename Data = int,
         typename KeyCompare = std::less<Key>,
         typename DataCompare = std::less<Data>,
         typename Hash = std::hash<Data>,
         typename HashValCompare = std::equal_to<Data>>
class RankList {
public:
    typedef RankList<Key, Data, KeyCompare, DataCompare, Hash, HashValCompare> self_type;
    typedef SkipList<Key, Data, KeyCompare, DataCompare> SkipListType;
    typedef std::unordered_map<Data, Key, Hash, HashValCompare> DictType;
    typedef typename SkipListType::iterator iterator;
    typedef typename SkipListType::const_iterator const_iterator;
    typedef typename SkipListType::val_type val_type;

    explicit RankList(const unsigned max_size = UINT32_MAX - 1) : _max_size(max_size) { }

    RankList(const self_type &rhs) :
            _rank_list(rhs._rank_list),
            _key_map(rhs._key_map),
            _max_size(rhs._max_size) { }

    self_type &operator=(const self_type &rhs) {
        if (this != std::addressof(rhs)) {
            _rank_list = rhs._rank_list;
            _key_map = rhs._key_map;
            _max_size = rhs._max_size;
        }
    }

    ~RankList() = default;

    bool Insert(const Key &key, const Data &identify) {
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

    void Delete(const Data &identify) {
        auto itr = _key_map.find(identify);
        if (_key_map.end() == itr)
            return;
        _rank_list.Delete(itr->second, itr->first);
        _key_map.erase(itr);
    }

    bool Update(const Key &key, const Data &identify) {
        auto finditr = _key_map.find(identify);

        if (finditr == _key_map.end())
            return Insert(key, identify);

        _rank_list.Delete(finditr->second, finditr->first);
        _rank_list.Insert(key, identify);
        finditr->second = key;

        return true;
    }

    unsigned long GetRank(const Data &identify) const {
        auto itr = _key_map.find(identify);
        if (itr == _key_map.end())
            return 0;
        return _rank_list.GetRank(itr->second, itr->first);
    }

    const_iterator GetByData(const Data &identify) const {
        auto itr = _key_map.find(identify);
        if (itr == _key_map.end())
            return end();
        return _rank_list.Search(itr->second, itr->first);
    }

    iterator GetByData(const Data &identify) {
        const_iterator itr = static_cast<const self_type&>(*this).GetByData(identify);
        return itr.remove_const();
    }

    const_iterator GetTopRank(const unsigned long rank) const {
        if (rank > _rank_list.Lenth())
            return _rank_list.end();
        return _rank_list.FirstInRangeByRank(Range(rank, rank));
    }

    iterator GetTopRank(const unsigned long rank) {
        const_iterator itr = static_cast<const self_type&>(*this).GetTopRank(rank);
        return itr.remove_const();
    }

    const_iterator GetFirstInRangeByScore(const Key &min, const Key &max) const {
        return _rank_list.FirstInRangeByScore(min, max);
    }

    iterator GetFirstInRangeByScore(const Key &min, const Key &max) {
        return _rank_list.FirstInRangeByScore(min, max);
    }

    const_iterator GetLastInRangeByScore(const Key &min, const Key &max) const {
        return _rank_list.LastInRangeByScore(min, max);
    }

    iterator GetLastInRangeByScore(const Key &min, const Key &max) {
        return _rank_list.LastInRangeByScore(min, max);
    }

    void Clear() {
        _rank_list.Clear();
        _key_map.clear();
    }

    unsigned long GetSize() const {
        return _rank_list.Lenth();
    }

    bool Empty() const { return _rank_list.Empty(); }

    iterator begin() { return _rank_list.begin(); }
    iterator end() { return _rank_list.end(); }
    iterator last() { return _rank_list.last(); }

    const_iterator begin() const { return _rank_list.begin(); }
    const_iterator end() const { return _rank_list.end(); }
    const_iterator last() const { return _rank_list.last(); }

private:
    SkipListType _rank_list;
    DictType _key_map;

    unsigned _max_size;
};

} //namespace lib_tools

#endif //SKIPLIST_RANKLIST_V1_H

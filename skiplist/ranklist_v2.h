// ranklist_v1.h
// @Created by czl17 on 2018-3-30.
// @brief ranklist implement by skiplist with hashtable
// Key             存储 key 值，例如分数值等，可重复，可自定义结构，需提供默认小于比较
// Data            存储用户数据，可用于唯一识别标志
// KeyCompare      Key 比较算法
// ValCompare      Data 比较算法
//
// func Insert     插入一个键值对, 存在则插入失败
// func Delete     删除用户数据
// func Update     更新一个键值对, 无则插入
// func GetSize    元素个数
// func GetRank    获取用户数据排行位置
// func GetByData  通过用户数据获取存储的元素, 返回迭代器
// func GetTopRank 返回排行第 top 的元素迭代器


#ifndef SKIPLIST_RANKLIST_V2_H
#define SKIPLIST_RANKLIST_V2_H

#include <unordered_map>
#include <map>

namespace lib_tools {

template<typename Key, typename Data = int,
         typename KeyCompare = std::less<Key>,
         typename ValCompare = std::equal_to<Data>>
class RankList {
public:
    typedef std::map<Key, Data, KeyCompare> ListType;
    typedef typename ListType::iterator iterator;

    explicit RankList(const unsigned max_size = UINT32_MAX - 1) : _max_size(max_size) { }

    ~RankList() = default;

    bool Insert(const Key &key, const Data &identify) {
        if (_key_map.find(identify) != _key_map.end())
            return false;
        if (!_key_map.insert(std::make_pair(identify, key)).second)
            return false;
        _rank_list.insert(std::make_pair(key, identify));

        if (_rank_list.size() > _max_size) {
            auto lastitr = _rank_list.rbegin();
            _key_map.erase(lastitr->second);
            _rank_list.erase(lastitr->first);
        }

        return true;
    }

    void Delete(const Data &identify) {
        auto itr = _key_map.find(identify);
        if (_key_map.end() == itr)
            return;
        _rank_list.erase(itr->first);
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

    unsigned long GetSize() {
        return _rank_list.Lenth();
    }

    unsigned long GetRank(const Data &identify) {
        auto itr = _key_map.find(identify);
        if (itr == _key_map.end())
            return 0;
        return _rank_list.GetRank(itr->second, itr->first);
    }

    iterator GetByData(const Data &identify) {
        auto itr = _key_map.find(identify);
        if (itr == _key_map.end())
            return end();
        return _rank_list.Search(itr->second, itr->first);
    }

    iterator GetTopRank(const unsigned long rank) {
        if (rank > _rank_list.Lenth())
            return _rank_list.end();
        return _rank_list.FirstInRangeByRank(Range(rank, rank));
    }

    bool Empty() { return _rank_list.Empty(); }

    void Clear() {
        _rank_list.Clear();
        _key_map.clear();
    }

    iterator begin() { return _rank_list.begin(); }
    iterator end() { return _rank_list.end(); }
    iterator last() { return _rank_list.last(); }

private:
    ListType _rank_list;
    std::unordered_map<Data, Key> _key_map;

    unsigned _max_size;
};

} //namespace lib_tools

#endif //SKIPLIST_RANKLIST_V2_H

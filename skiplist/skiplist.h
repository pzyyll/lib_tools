// skiplist.h
// @Created by czllo on 2017/4/9.
// @date Update on 2018/3/30
// @brief A ranklist implement by skiplist.
//        key 可以自定义结构，并且提供合适的小于操作.

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <string>
#include <vector>
#include <type_traits>
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

namespace lib_tools {

#define SKIPLIST_P 0.25
#define MAXLEVEL 32

inline int skRandomLevel() {
    int lvl = 1;
    while ((rand() < (SKIPLIST_P * RAND_MAX)) && (lvl < MAXLEVEL))
        ++lvl;
    return lvl;
}

struct Range {
    Range(unsigned long long min_, unsigned long long max_)
            : rmin(min_), rmax(max_) { }
    ~Range() { }

    unsigned long long rmin;
    unsigned long long rmax;
};

template <typename T>
struct SkipListNode {
    typedef T val_type;
    typedef SkipListNode<T> self_type;
    typedef self_type* pointer;

    //template <typename Tp> struct rebind { typedef SkipListNode<Tp> othre; };

    SkipListNode(int lvl, val_type val, unsigned lru = 0)
            : //score(score),
              data(val),
              backward(NULL) {
        level.resize(lvl);
    }
    ~SkipListNode() { }

    struct SkipListLevel {
        SkipListLevel() : forward(NULL), span(0) { }
        pointer forward;
        unsigned span;
    } /*level[]*/;

    val_type data;
    pointer backward;
    std::vector<SkipListLevel> level;
};

template <typename Tp>
struct SkipListIterator {
public:
    typedef Tp val_type;
    typedef Tp* pointer;
    typedef Tp& reference;
    typedef SkipListIterator<Tp> self_type;
    typedef SkipListNode<val_type>* sl_node_pointer;

    SkipListIterator()
            : pos(nullptr), end(nullptr) { }
    SkipListIterator(sl_node_pointer it_, sl_node_pointer end_)
            : pos(it_), end(end_) { }

    reference operator*() { return pos->data; }
    pointer operator->() { return &(operator*()); }

    self_type &operator++() {
        assert(pos != end);
        pos = pos->level[0].forward;
        return *this;
    }
    const self_type operator++(int) {
        self_type tmp(*this);
        ++*this;
        return tmp;
    }
    self_type &operator--() {
        assert(pos != end);
        pos = pos->backward;
        return *this;
    }
    const self_type operator--(int) {
        self_type tmp(*this);
        --*this;
        return tmp;
    }

    bool operator==(const self_type &it) const { return pos == it.pos; }
    bool operator!=(const self_type &it) const { return pos != it.pos; }

    // The actual data
    sl_node_pointer pos, end;
};


template <typename Tp>
struct SkipListConstIterator {
public:
    typedef Tp val_type;
    typedef const Tp* pointer;
    typedef const Tp& reference;
    typedef SkipListIterator<Tp> iterator;
    typedef SkipListConstIterator<Tp> self_type;
    typedef SkipListNode<val_type>* sl_node_pointer;

    SkipListConstIterator()
            : pos(nullptr), end(nullptr) { }
    SkipListConstIterator(const iterator &it)
            : pos(it.pos), end(it.end) { }
    SkipListConstIterator(sl_node_pointer it_, sl_node_pointer end_)
            : pos(it_), end(end_) { }

    reference operator*() { return pos->data; }
    pointer operator->() { return &(operator*()); }

    iterator remove_const() { return iterator(pos, end); }

    self_type &operator++() {
        assert(pos != end);
        pos = pos->level[0].forward;
        return *this;
    }
    const self_type operator++(int) {
        self_type tmp(*this);
        ++*this;
        return tmp;
    }
    self_type &operator--() {
        assert(pos != end);
        pos = pos->backward;
        return *this;
    }
    const self_type operator--(int) {
        self_type tmp(*this);
        --*this;
        return tmp;
    }

    bool operator==(const self_type &it) const { return pos == it.pos; }
    bool operator!=(const self_type &it) const { return pos != it.pos; }

private:
    sl_node_pointer pos, end;
};


template <typename Key, typename Tp,
          typename KeyCmp = std::less<Key>,
          typename DataCmp = std::less<Tp>,
          typename Alloc = std::allocator<Tp>>
class SkipList {
public:
    typedef Key key_type;
    typedef Tp data_type;
    typedef std::pair<const key_type, const data_type> val_type;
    typedef SkipListNode<val_type> sl_node;
    typedef sl_node* sl_node_pointer;
    typedef KeyCmp key_cmp_type;
    typedef DataCmp data_cmp_type;
    typedef typename Alloc::template rebind<sl_node>::other node_alloc;
    typedef SkipList<Key, Tp, KeyCmp, DataCmp, Alloc> self_type;
    typedef val_type& reference;
    typedef val_type* pointer;
    typedef const val_type& const_referrence;
    typedef const val_type* const_pointer;
    typedef SkipListIterator<val_type> iterator;
    typedef SkipListConstIterator<val_type> const_iterator;

    SkipList()
            : head_(NULL),
              tail_(NULL),
              lenth_(0),
              level_(1)
    {
        InitHead();
    };

    SkipList(const self_type &rhs)
            : head_(NULL),
              tail_(NULL),
              lenth_(0),
              level_(1) {
        CopyFrom(rhs);
    }

    self_type &operator=(const self_type &rhs) {
        CopyFrom(rhs);
    }

    ~SkipList() {
        Deinit();
    };

    const_iterator Search(key_type score, const data_type &val) const {
        if (Empty()) return end();

        sl_node_pointer x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (NULL != x->level[i].forward &&
                    (key_cmp_(x->level[i].forward->data.first, score) ||
                     (KeyEqual(x->level[i].forward->data.first, score) &&
                      data_cmp_(x->level[i].forward->data.second, val))))
                x = x->level[i].forward;
        }

        x = x->level[0].forward;
        if (x != NULL &&
             KeyEqual(score, x->data.first) &&
              DataEqual(val, x->data.second))
            return iterator(x, tail_->level[0].forward);
        return end();
    }

    iterator Search(key_type score, const data_type &val) {
        const_iterator itr = static_cast<const self_type&>(*this).Search(score, val);
        return itr.remove_const();
    }

    //@brief when mutil score is same, search the first iteratro.
    const_iterator SearchFirst(key_type score) const {
        if (Empty()) return end();

        sl_node_pointer x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (NULL != x->level[i].forward &&
                    key_cmp_(x->level[i].forward->data.first, score)) {
                x = x->level[i].forward;
            }
        }

        x = x->level[0].forward;
        if (x != NULL && KeyEqual(score, x->data.first))
            return iterator(x, tail_->level[0].forward);
        return end();
    }

    iterator SearchFirst(key_type score) {
        const_iterator itr = static_cast<const self_type&>(*this).SearchFirst(score);
        return itr.remove_const();
    }

    unsigned long GetRank(key_type score, const data_type &val) const {
        if (Empty()) return 0;

        unsigned long rank = 0;
        sl_node_pointer x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (NULL != x->level[i].forward &&
                   (key_cmp_(x->level[i].forward->data.first, score) ||
                    (KeyEqual(x->level[i].forward->data.first, score) &&
                     !data_cmp_(val, x->level[i].forward->data.second)))) {
                rank += x->level[i].span;
                x = x->level[i].forward;
            }

            if (DataEqual(x->data.second, val)) {
                return rank;
            }
        }
        return 0;
    }

    const_iterator FirstInRangeByRank(const Range &range) const {
        if (Empty()) return end();

        unsigned long min = range.rmin;
        unsigned long max = range.rmax;
        if (max < min) {
            return end();
        } else if (min > lenth_) {
            return end();
        }

        sl_node_pointer x;
        unsigned long traversed = 0;
        x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (x->level[i].forward &&
                    (traversed + x->level[i].span) < min) {
                traversed += x->level[i].span;
                x = x->level[i].forward;
            }
        }
        ++traversed;
        x = x->level[0].forward;
        if (NULL == x || traversed > max)
            return end();
        return iterator(x, tail_->level[0].forward);
    }

    iterator FirstInRangeByRank(const Range &range) {
        const_iterator itr = static_cast<const self_type&>(*this).FirstInRangeByRank(range);
        return itr.remove_const();
    }

    const_iterator FirstInRangeByScore(const key_type &min, const key_type &max) const {
        if (Empty()) return end();

        //max < min
        if (key_cmp_(max, min))
            return end();

        //tail_->data.key_val.first < min
        if (key_cmp_(tail_->data.first, min))
            return end();

        sl_node_pointer x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (x->level[i].forward &&
                    key_cmp_(x->level[i].forward->data.first, min))
                x = x->level[i].forward;
        }
        x = x->level[0].forward;
        assert(x != NULL);

        //注意找到的节点分数不要大于max
        if (key_cmp_(max, x->data.first))
            return end();

        return iterator(x, tail_->level[0].forward);
    }

    iterator FirstInRangeByScore(const key_type &min, const key_type &max) {
        const_iterator itr =
                static_cast<const self_type&>(*this).FirstInRangeByScore(min, max);
        return itr.remove_const();
    }

    const_iterator LastInRangeByScore(const key_type &min, const key_type &max) const {
        if (Empty()) return end();

        //max < min
        if (key_cmp_(max, min))
            return end();

        //tail_->data.key_val.first < min
        if (key_cmp_(tail_->data.first, min)) {
            return end();
        }

        if (!key_cmp_(max, tail_->data.first)) {
            return iterator(tail_, tail_->level[0].forward);
        }

        sl_node_pointer x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (x->level[i].forward &&
                    !key_cmp_(max, x->level[i].forward->data.first)) {
                x = x->level[i].forward;
            }
        }

        assert(x != NULL);

        //x->data.key_val.first < min
        if (key_cmp_(x->data.first, min)) {
            return end();
        }

        return iterator(x, tail_->level[0].forward);
    }

    iterator LastInRangeByScore(const key_type &min, const key_type &max) {
        const_iterator itr =
                static_cast<const self_type&>(*this).LastInRangeByScore(min, max);
        return itr.remove_const();
    }

    int Insert(key_type score, const data_type &val) {
        sl_node_pointer update[MAXLEVEL], x;
        int ranks[MAXLEVEL] = {0};

        x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            ranks[i] = i == (level_ - 1) ? 0 : ranks[i + 1];
            while (NULL != x->level[i].forward &&
                    (key_cmp_(x->level[i].forward->data.first, score) ||
                      (KeyEqual(x->level[i].forward->data.first, score) &&
                       data_cmp_(x->level[i].forward->data.second, val)))) {
                ranks[i] += x->level[i].span;
                x = x->level[i].forward;
            }
            update[i] = x;
        }

        //
        //分值可重复，需保证调用此函数时该成员不存在
        //
        int lvl = skRandomLevel();
        if (lvl > level_) {
            for (int i = level_; i < lvl; ++i) {
                ranks[i] = 0;
                update[i] = head_;
                update[i]->level[i].span = lenth_;
            }
            level_ = lvl;
        }

        x = MakeNode(lvl, score, val);
        for (int i = 0; i < lvl; ++i) {
            x->level[i].forward = update[i]->level[i].forward;
            update[i]->level[i].forward = x;

            x->level[i].span = update[i]->level[i].span - (ranks[0] - ranks[i]);
            update[i]->level[i].span = (ranks[0] - ranks[i]) + 1;
        }

        for (int i = lvl; i < level_; ++i) {
            update[i]->level[i].span++;
        }

        x->backward = (update[0] == head_ ) ? NULL : update[0];
        if (x->level[0].forward)
            x->level[0].forward->backward = x;
        else
            tail_ = x;
        ++lenth_;

        return 0;
    }

    int Delete(key_type score, const data_type &val) {
        sl_node_pointer update[MAXLEVEL], x;
        x = head_;
        for (int i = level_ - 1; i >= 0; --i) {
            while (NULL != x->level[i].forward &&
                    (key_cmp_(x->level[i].forward->data.first, score) ||
                      (KeyEqual(x->level[i].forward->data.first, score) &&
                       data_cmp_(x->level[i].forward->data.second, val)))) {
                x = x->level[i].forward;
            }
            update[i] = x;
        }
        x = x->level[0].forward;
        if (NULL != x &&
             KeyEqual(score, x->data.first) &&
              DataEqual(x->data.second, val)) {
            DeleteNode(x, update);
            FreeNode(x);
            return 0;
        }

        return -1; //not found
    }

    int Delete(iterator itr) {
        if (itr == end())
            return -1;
        return Delete(itr->first, itr->second);
    }

    void Clear() {
        Deinit();
        InitHead();
    }

    void CopyFrom(const self_type &from) {
        if (this != std::addressof(from)) {
            Clear();
            const_iterator iter = from.begin();
            for (; iter != from.end(); ++iter) {
                this->Insert(iter->first, iter->second);
            }
        }
    }

    unsigned long Lenth() const { return lenth_; }

    bool Empty() const { return Lenth() == 0; }

    iterator begin() { return iterator(head_->level[0].forward, nullptr); }
    iterator end() { return iterator(nullptr, nullptr); }
    iterator last() { return iterator(tail_, nullptr); }

    const_iterator begin() const { return const_iterator(head_->level[0].forward, nullptr); }
    const_iterator end() const { return const_iterator(nullptr, nullptr); }
    const_iterator last() const { return const_iterator(tail_, nullptr); }

private:
    void InitHead() {
        head_ = MakeNode(MAXLEVEL, key_type(), data_type());
        for (int i = 0; i < MAXLEVEL; ++i) {
            head_->level[i].forward = NULL;
            head_->level[i].span = 0;
        }
        head_->backward = NULL;
    }

    void DeleteNode(sl_node_pointer x, sl_node_pointer update[]) {
        for (int i = 0; i < level_; ++i) {
            if (update[i]->level[i].forward == x) {
                update[i]->level[i].span += x->level[i].span - 1;
                update[i]->level[i].forward = x->level[i].forward;
            } else {
                update[i]->level[i].span -= 1;
            }
        }

        if (NULL != x->level[0].forward) {
            x->level[0].forward->backward = x->backward;
        } else {
            tail_ = x->backward;
        }

        while (level_ > 1 && NULL == head_->level[level_-1].forward)
            --level_;
        --lenth_;
    }

    sl_node_pointer MakeNode(const int lvl,
            const key_type &score,
            const data_type &data) {
        sl_node_pointer pNode = alloc_.allocate(1);
        alloc_.construct(pNode, lvl, std::make_pair(score, data));

#ifdef CHECK_MALLOC
        static int make = 0;
        std::cout << "Make:" << ++make << std::endl;
#endif
        return pNode;
    }

    int FreeNode(sl_node_pointer node) {
        alloc_.destroy(node);
        alloc_.deallocate(node, 1);
        node = NULL;

#ifdef CHECK_MALLOC
        static int free = 0;
        std::cout << "Free:" << ++free << std::endl;
#endif
        return 0;
    }

    void Deinit() {
        sl_node_pointer itr = head_;
        sl_node_pointer next = NULL;
        while(itr != NULL) {
            next = itr->level[0].forward;
            FreeNode(itr);
            itr = next;
        }
        head_ = NULL;
        tail_ = NULL;
        lenth_ = 0;
        level_ = 1;
    }

    bool KeyEqual(const key_type &key1, const key_type &key2) const {
        return (!key_cmp_(key1, key2) && !key_cmp_(key2, key1));
    }

    bool DataEqual(const data_type &val1, const data_type &val2) const {
        return (!data_cmp_(val1, val2) && !data_cmp_(val2, val1));
    }

private:
    sl_node_pointer head_, tail_;
    unsigned long lenth_;
    int level_;

    node_alloc alloc_;
    key_cmp_type key_cmp_;
    data_cmp_type data_cmp_;
};

} //namespace lib_tools
#endif //SKIPLIST_SKIPLIST_H

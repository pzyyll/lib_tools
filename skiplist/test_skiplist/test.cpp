#include "gtest/gtest.h"
#include "skiplist.h"

#include <map>

namespace {

using namespace lib_tools;
using namespace std;

struct Key {
    Key(const int sc = 0, const int t = 0) : score(sc), tm(t) { }
    ~Key() = default;

    bool operator<(const Key &k) const {
        if (score != k.score)
            return score < k.score;
        return tm < k.tm;
    } 

    bool operator==(const Key &k) const {
        if (score != k.score)
            return false;
        return tm == k.tm;
    }

    int score;
    int tm;
};

typedef lib_tools::SkipList<Key, int> RankType;
typedef std::multimap<Key, int> MapType;

class SkiplistTest : public ::testing::Test {
protected:
    void SetUp() override {
        //设置测试用例
        test_case_.push_back(std::make_pair(Key(12, 0), 6));
        test_case_.push_back(std::make_pair(Key(1, 0), 1));
        test_case_.push_back(std::make_pair(Key(10, 0), 2));
        test_case_.push_back(std::make_pair(Key(5, 0), 3));
        test_case_.push_back(std::make_pair(Key(12, 0), 4));
        test_case_.push_back(std::make_pair(Key(8, 0), 5));
        
        rank0_.Insert(test_case_[0].first, test_case_[0].second);
        rank0_.Insert(test_case_[1].first, test_case_[1].second);
        rank0_.Insert(test_case_[2].first, test_case_[2].second);
        rank0_.Insert(test_case_[3].first, test_case_[3].second);
        rank0_.Insert(test_case_[4].first, test_case_[4].second);
        rank0_.Insert(test_case_[5].first, test_case_[5].second);

        map_sort_.insert(test_case_[0]);
        map_sort_.insert(test_case_[1]);
        map_sort_.insert(test_case_[2]);
        map_sort_.insert(test_case_[3]);
        map_sort_.insert(test_case_[4]);
        map_sort_.insert(test_case_[5]);
    }
    
    RankType rank0_;
    RankType rank1_;
    RankType rank2_; // test_copy
    MapType map_sort_;  //与标准库的排序做比较，从而确定排序结果是否正确
    std::vector<std::pair<Key, int>> test_case_;
};

TEST_F(SkiplistTest, Lenth) {
    EXPECT_EQ(0, rank1_.Lenth());
    EXPECT_EQ(6, rank0_.Lenth());
}

TEST_F(SkiplistTest, Search) {
    auto itr = rank0_.Search(Key(10, 0), 2);
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(2, itr->second) << "Search un match.";
    EXPECT_EQ(10, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.Search(Key(9, 0), 2);
    ASSERT_TRUE(itr == rank0_.end());

    itr = rank0_.Search(Key(10, 0), 1);
    ASSERT_TRUE(itr == rank0_.end());
}

TEST_F(SkiplistTest, SearchFirst) {
    auto itr = rank0_.SearchFirst(Key(12, 0));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(4, itr->second) << "SearchFirst un match.";
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.SearchFirst(Key(1, 0));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(1, itr->second) << "SearchFirst un match.";
    EXPECT_EQ(1, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.SearchFirst(Key(13, 0));
    ASSERT_TRUE(itr == rank0_.end());

    itr = rank0_.SearchFirst(Key(0, 0));
    ASSERT_TRUE(itr == rank0_.end());
}

TEST_F(SkiplistTest, GetRank) {
    auto rank = rank0_.GetRank(Key(10, 0), 2);
    EXPECT_EQ(4, rank) << "GetRank info un match.";

    auto rank1 = rank0_.GetRank(Key(1, 0), 1);
    EXPECT_EQ(1, rank1);

    auto rank2 = rank0_.GetRank(Key(12, 0), 4);
    EXPECT_EQ(5, rank2);

    auto rank3 = rank0_.GetRank(Key(12, 0), 6);
    EXPECT_EQ(6, rank3);

    auto rank_end = rank0_.GetRank(Key(0, 0), 0);
    EXPECT_EQ(0, rank_end);

    rank_end = rank0_.GetRank(Key(0, 0), 1);
    EXPECT_EQ(0, rank_end);

    rank_end = rank0_.GetRank(Key(12, 0), 0);
    EXPECT_EQ(0, rank_end);
}

TEST_F(SkiplistTest, FirstInRangeByRank) {
    auto itr = rank0_.FirstInRangeByRank(Range(0, 2));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(1, itr->second);
    EXPECT_EQ(1, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByRank(Range(3, 5));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(5, itr->second);
    EXPECT_EQ(8, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByRank(Range(6, 10));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByRank(Range(1, 1));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(1, itr->second);
    EXPECT_EQ(1, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);


    itr = rank0_.FirstInRangeByRank(Range(3, 3));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(5, itr->second);
    EXPECT_EQ(8, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByRank(Range(6, 6));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByRank(Range(7, 10));
    ASSERT_TRUE(itr == rank0_.end());

    itr = rank0_.FirstInRangeByRank(Range(4, 2));
    ASSERT_TRUE(itr == rank0_.end());
}

TEST_F(SkiplistTest, FirstInRangeByScore) {
    auto itr = rank0_.FirstInRangeByScore(Key(0, 0), Key(9, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(1, itr->second);
    EXPECT_EQ(1, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByScore(Key(9, 0), Key(100, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(2, itr->second);
    EXPECT_EQ(10, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByScore(Key(12, 0), Key(100, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(4, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByScore(Key(12, 0), Key(12, 0));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(4, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.FirstInRangeByScore(Key(100, 0), Key(200, 0));
    ASSERT_TRUE(itr == rank0_.end());

    itr = rank0_.FirstInRangeByScore(Key(10, 0), Key(9, 0));
    ASSERT_TRUE(itr == rank0_.end());
}

TEST_F(SkiplistTest, LastInRangeByScore) {
    auto itr = rank0_.LastInRangeByScore(Key(0, 0), Key(9, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(5, itr->second);
    EXPECT_EQ(8, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.LastInRangeByScore(Key(0, 0), Key(100, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.LastInRangeByScore(Key(12, 0), Key(100, 100));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.LastInRangeByScore(Key(12, 0), Key(12, 0));
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    itr = rank0_.LastInRangeByScore(Key(13, 0), Key(100, 0));
    ASSERT_TRUE(itr == rank0_.end());

    itr = rank0_.LastInRangeByScore(Key(12, 0), Key(11, 0));
    ASSERT_TRUE(itr == rank0_.end());
}

TEST_F(SkiplistTest, Delete) {
    int ret = rank0_.Delete(test_case_[0].first, test_case_[0].second);
    EXPECT_EQ(0, ret);
    EXPECT_EQ(5, rank0_.Lenth());

    MapType sample0;
    sample0.insert(test_case_[1]);
    sample0.insert(test_case_[2]);
    sample0.insert(test_case_[3]);
    sample0.insert(test_case_[4]);
    sample0.insert(test_case_[5]);

    EXPECT_EQ(sample0.size(), rank0_.Lenth());
    auto rank_itr = rank0_.begin();
    auto map_itr = sample0.begin();

    unsigned cnt = 0;
    for ( ; 
        rank_itr != rank0_.end() && map_itr != map_sort_.end(); 
        ++rank_itr, ++map_itr) {
        EXPECT_EQ((*rank_itr).first, (*map_itr).first);
        EXPECT_EQ((*rank_itr).second, (*map_itr).second);
        ++cnt;
    }

    EXPECT_EQ(cnt, rank0_.Lenth());
    EXPECT_EQ(cnt, sample0.size());

    ret = rank0_.Delete(test_case_[0].first, 100);
    EXPECT_EQ(-1, ret);

    ret = rank0_.Delete(Key(100,100), test_case_[0].second);
    EXPECT_EQ(-1, ret);

    EXPECT_EQ(5, rank0_.Lenth());
}

TEST_F(SkiplistTest, Clear) {
    rank0_.Clear();
 
    EXPECT_EQ(0, rank0_.Lenth());

    rank0_.Insert(test_case_[1].first, test_case_[1].second);
    rank0_.Insert(test_case_[2].first, test_case_[2].second);
    rank0_.Insert(test_case_[3].first, test_case_[3].second);

    map_sort_.clear();
    map_sort_.insert(test_case_[1]);
    map_sort_.insert(test_case_[2]);
    map_sort_.insert(test_case_[3]);

    EXPECT_EQ(map_sort_.size(), rank0_.Lenth());
    auto rank_itr = rank0_.begin();
    auto map_itr = map_sort_.begin();

    unsigned cnt = 0;
    for ( ; 
        rank_itr != rank0_.end() && map_itr != map_sort_.end(); 
        ++rank_itr, ++map_itr) {
        EXPECT_EQ((*rank_itr).first, (*map_itr).first);
        EXPECT_EQ((*rank_itr).second, (*map_itr).second);
        ++cnt;
    }

    EXPECT_EQ(cnt, rank0_.Lenth());
    EXPECT_EQ(cnt, map_sort_.size());
}

TEST_F(SkiplistTest, last) {
    auto itr = rank0_.last();
    ASSERT_TRUE(itr != rank0_.end());
    EXPECT_EQ(6, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);

    
    ASSERT_TRUE(++itr == rank0_.end());

    itr = rank0_.last();
    ASSERT_TRUE(--itr != rank0_.end());
    EXPECT_EQ(4, itr->second);
    EXPECT_EQ(12, (*itr).first.score);
    EXPECT_EQ(0, (*itr).first.tm);
}

TEST_F(SkiplistTest, TestSortWithStdMap) {
    EXPECT_EQ(map_sort_.size(), rank0_.Lenth());
    auto rank_itr = rank0_.begin();
    auto map_itr = map_sort_.begin();

    unsigned cnt = 0;
    for ( ; 
        rank_itr != rank0_.end() && map_itr != map_sort_.end(); 
        ++rank_itr, ++map_itr) {
        EXPECT_EQ((*rank_itr).first, (*map_itr).first);
        EXPECT_EQ((*rank_itr).second, (*map_itr).second);
        ++cnt;
    }

    EXPECT_EQ(cnt, rank0_.Lenth());
    EXPECT_EQ(cnt, map_sort_.size());
}

TEST_F(SkiplistTest, TestCopyFrom) {
    rank2_.CopyFrom(rank0_);

    EXPECT_EQ(rank2_.Lenth(), rank0_.Lenth());

    auto rank2_itr = rank2_.begin();
    auto rank0_itr = rank0_.begin();
    //auto map_itr = map_sort_.begin();

    unsigned cnt = 0;
    for ( ;
        rank2_itr != rank2_.end() && rank0_itr != rank0_.end();
        ++rank2_itr, ++rank0_itr) {
        EXPECT_EQ(rank2_itr->first, rank0_itr->first);
        EXPECT_EQ(rank2_itr->second, rank0_itr->second);
        //EXPECT_EQ(rank2_itr->first, map_itr->first);
        //EXPECT_EQ(rank2_itr->second, map_itr->second);
        ++cnt;
    }

    EXPECT_EQ(cnt, rank2_.Lenth());
    EXPECT_EQ(cnt, rank0_.Lenth());


    auto trank0(rank0_);
    EXPECT_EQ(trank0.Lenth(), rank0_.Lenth());
    auto trank0_itr = trank0.begin();
    rank0_itr = rank0_.begin();
    cnt = 0;
    for ( ;
            trank0_itr != trank0.end() && rank0_itr != rank0_.end();
            ++trank0_itr, ++rank0_itr) {
        EXPECT_EQ(trank0_itr->first, rank0_itr->first);
        EXPECT_EQ(trank0_itr->second, rank0_itr->second);
        ++cnt;
    }
    EXPECT_EQ(cnt, rank0_.Lenth());


    RankType trank1;
    trank1 = rank0_;
    EXPECT_EQ(trank1.Lenth(), rank0_.Lenth());
    auto trank1_itr = trank1.begin();
    rank0_itr = rank0_.begin();
    cnt = 0;
    for ( ;
            trank1_itr != trank1.end() && rank0_itr != rank0_.end();
            ++trank1_itr, ++rank0_itr) {
        EXPECT_EQ(trank1_itr->first, rank0_itr->first);
        EXPECT_EQ(trank1_itr->second, rank0_itr->second);
        ++cnt;
    }
    EXPECT_EQ(cnt, rank0_.Lenth());
}


} //nick namespace

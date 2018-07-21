#include "gtest/gtest.h"
#include "ranklist_v1.h"

#include <map>

namespace {

using namespace lib_tools;
using namespace std;

struct Key {
    Key(const int sc = 0, const int t = 0) : score(sc), tm(t) { }
    ~Key() = default;

    bool operator<(const Key &k) const {
        if (score != k.score)
            return score > k.score;
        return tm > k.tm;
    }

    bool operator==(const Key &k) const {
        if (score != k.score)
            return false;
        return tm == k.tm;
    }

    int score;
    int tm;
};

typedef lib_tools::RankList<Key, int> RankType;
typedef std::multimap<Key, int> MapType;

class RankListTest : public ::testing::Test {
protected:
    RankListTest() : rank0_(5), rank1_() {  }

    void SetUp() override {
        //设置测试用例
        test_case_.push_back(std::make_pair(Key(12, 0), 6));
        test_case_.push_back(std::make_pair(Key(1, 0), 1));
        test_case_.push_back(std::make_pair(Key(10, 0), 2));
        test_case_.push_back(std::make_pair(Key(5, 0), 3));
        test_case_.push_back(std::make_pair(Key(12, 99), 4));
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
    MapType map_sort_;  //与标准库的排序做比较，从而确定排序结果是否正确
    std::vector<std::pair<Key, int>> test_case_;
};

TEST_F(RankListTest, GetSize) {
    EXPECT_EQ(0, rank1_.GetSize());
    EXPECT_EQ(5, rank0_.GetSize());
}

TEST_F(RankListTest, Last) {
    EXPECT_EQ(rank0_.last()->first, Key(5, 0));
    EXPECT_EQ(rank0_.last()->second, 3);
}

TEST_F(RankListTest, TestSortWithStdMap) {
    //EXPECT_EQ(map_sort_.size(), rank0_.GetSize());
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

    EXPECT_EQ(cnt, rank0_.GetSize());
    //EXPECT_EQ(cnt, map_sort_.size());
}

TEST_F(RankListTest, TestGetByData) {
    auto finditr = rank0_.GetByData(2);

    EXPECT_EQ((*finditr).first, Key(10, 0));
    EXPECT_EQ((*finditr).second, 2);
}

TEST_F(RankListTest, GetFirstInRangeByScore) {
    auto itr = rank0_.GetFirstInRangeByScore(Key(0, 0), Key(12, 99));

    EXPECT_EQ(itr, rank0_.end());

    itr = rank0_.GetFirstInRangeByScore(Key(12, 0), Key(0, 0));
    EXPECT_EQ(itr->first, Key(12, 0));

    itr = rank0_.GetFirstInRangeByScore(Key(12, 999), Key(0, 0));
    EXPECT_EQ(itr->first, Key(12, 99));
}

TEST_F(RankListTest, GetLastInRangeByScore) {
    auto itr = rank0_.GetLastInRangeByScore(Key(12, 0), Key(0, 0));

    EXPECT_EQ(itr->first, Key(5, 0));
    EXPECT_EQ(itr->second, 3);
}

TEST_F(RankListTest, GetLastInRangeByScoreEmpty) {
    auto itr = rank1_.GetLastInRangeByScore(Key(12, 0), Key(0, 0));
    EXPECT_EQ(itr, rank1_.end());
}

TEST_F(RankListTest, ConstGetLastInRangeByScore) {
    const auto &const_rank0 = rank0_;

    RankType::const_iterator itr = const_rank0.GetLastInRangeByScore(Key(12, 0), Key(0, 0));

    EXPECT_EQ(itr->first, Key(5, 0));
    EXPECT_EQ(itr->second, 3);
}

} //nick namespace

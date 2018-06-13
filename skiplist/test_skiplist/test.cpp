#include "gtest/gtest.h"
#include "skiplist.h"

TEST(TestSkiplist, Skiplist) {
    lib_tools::SkipList<int, int> skip_rank;
    EXPECT_EQ(0, skip_rank.Lenth()) << "Skip mes.";
}

TEST(Test, Fails) {
    EXPECT_EQ(1, 1) << "Success mes.";
    EXPECT_EQ(1, 2) << "Fail mes.";
}

#include "gtest/gtest.h"


TEST(Test, Fails) {
    EXPECT_EQ(1, 2) << "Fail mes.";
    EXPECT_EQ(1, 1) << "Success mes.";
}

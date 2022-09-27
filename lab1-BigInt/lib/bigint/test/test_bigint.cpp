#include "gtest/gtest.h"
#include "big_int.h"

TEST(S,S){
    EXPECT_EQ(1,1);
}

TEST(BI,s){
    BigInt s;
    s.size();
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
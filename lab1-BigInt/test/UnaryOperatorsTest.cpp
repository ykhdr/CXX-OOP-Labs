//#include "gtest/gtest.h"

#include <gtest/gtest.h>
#include "../src/BigInt.h"


TEST(OpPlusPlusTest,ShouldAdd1ToNumber)
{
    // small number test
    BigInt num = BigInt(100);
    EXPECT_EQ(static_cast<int>(++num),101);


    // transition cell test
    num = BigInt("999999999");
    EXPECT_EQ(static_cast<int>(++num),1000000000);


}
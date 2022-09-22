#include <iostream>
#include "BigInt.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ
 *
 *
 */
//999999999
//100000000   8
int main() {
    std::string str = "999999999";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("999999999");
    num += num2;
    std::cout << num.operator std::string() << std::endl;



}
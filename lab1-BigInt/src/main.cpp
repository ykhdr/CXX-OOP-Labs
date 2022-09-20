#include <iostream>
#include "BigInt.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ 8 СИМВОЛОВ
 *
 *
 */
 //1000000000
 //999999990
 //1000000000
int main() {
    std::string str = "-10";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt(1000000000);
    num+=num2;
    std::cout << num.operator std::string() << std::endl;


}
#include <iostream>
#include "BigInt.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО
 * REMAINDER_LENGTH ДЛЯ ВЫСШИХ РАЗРЯДОВ
 */

//1000000000
//1000000001
//1000000000
//1999999998
int main() {
    std::string str = "0000000000000000000000000000005";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("0");
    num += num2;

    std::cout << num.size() << "    " <<num.operator std::string() << std::endl;



}
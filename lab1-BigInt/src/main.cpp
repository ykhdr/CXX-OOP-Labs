#include <iostream>
#include "BigInt.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ 8 СИМВОЛОВ
 *
 *
 */
//111111112
//111111111
//10000000000
//9999999999
int main() {
    std::string str = "-111111111";//FIXME: переделывать всё.
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("-1111111");
    std::cout << num.size() << " " << num.operator std::string() << std::endl;
    std::cout << static_cast<bool>(num2 > num) << std::endl;
}
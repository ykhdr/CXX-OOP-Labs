#include <iostream>
#include <valarray>
#include "BigInt/BigInt.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 * REMAINDER_LENGTH ДЛЯ ВЫСШИХ РАЗРЯДОВ \n
 */


int main() {
    std::string str = "-100000000000000000000010";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("-100000000000");
    num *= num2;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;

}
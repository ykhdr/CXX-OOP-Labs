#include <iostream>
#include <valarray>

#include "big_int.h"

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 */

int main() {
    std::string str = "10";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("7");
    num /= num2;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;
    return 0;
}
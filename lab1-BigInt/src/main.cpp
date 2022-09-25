#include <iostream>
#include <valarray>
#include "BigInt.h"


/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 * REMAINDER_LENGTH ДЛЯ ВЫСШИХ РАЗРЯДОВ \n
 */

//21312312321340000000 -- don't work
//11213123231287
int main() {
    std::string str = "21312312321340000000";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("11213123231287");
    num /= num2;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;
}
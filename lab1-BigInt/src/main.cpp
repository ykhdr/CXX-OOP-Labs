#include <iostream>
#include <valarray>
#include "BigInt.h"


/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 * REMAINDER_LENGTH ДЛЯ ВЫСШИХ РАЗРЯДОВ \n
 */

//21312312321340000000 -- work
//11213123231287

//6497725788823911
//6497725788823911
int main() {
    std::string str = "-123456789987654321"; //don't work with minus
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("11111111111111"); //удалить минусы из строки
    num /= num2;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;
}
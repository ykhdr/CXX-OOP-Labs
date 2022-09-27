#include <iostream>
#include <valarray>

#include "big_int.h"


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
    std::string str = "10";
    big_int num = big_int(str);
    big_int num2 = big_int("7");
    num = ~num;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;
}
#include <iostream>
#include <valarray>

#include "../lib/bigint/include/big_int.h"


/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 */

//21312312321340000000 -- work
//11213123231287

//6497725788823911
//6497725788823911
int main() {
    std::string str = "10";
    BigInt num = BigInt(str);
    BigInt num2 = BigInt("7");
    num = ~num;

    std::cout << num.size() << "    " << static_cast<std::string>(num) << std::endl;
    return 0;
}
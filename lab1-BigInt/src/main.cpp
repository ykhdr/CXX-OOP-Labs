#include "bigint.h"
#include <bitset>
#include <iostream>

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 */

int main() {

    std::bitset<32> b1 (21847);
    std::cout << b1 << std::endl;
    std::bitset<32> b2 (-21930*(-1));
    std::cout << b2 <<std::endl;
    std::cout << std::bitset<32>(21847 | -21930);
    return 0;
}
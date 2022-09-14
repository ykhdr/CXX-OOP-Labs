#include <iostream>
#include "BigInt.h"

//TODO: подумать над тем, как реализоваывать хранение числа. Может создать структуру, где будет запись о длине каждой ячейки?
//TODO: или же достаточно просто знать длину последнего слота

int main() {
    std::string str = "90001110101"; // 9 chars
    auto num = new BigInt(str);
    auto num2 = new BigInt(*num);
    std::cout << num2->size() <<" "<<num2->operator std::string();
}
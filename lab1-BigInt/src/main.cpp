#include "bigint.h"
#include <iostream>

/**
 * ЯЧЕЙКА ХРАНИТ 9 СИМВОЛОВ \n
 * ЕСЛИ ЕСТЬ ЗНАК, ТО ПЕРВАЯ ЯЧЕЙКА ХРАНИТ ТАКЖЕ 9 СИМВОЛОВ \n
 * ХРАНИТСЯ ПЕРЕВЕРНУТОЕ ЧИСЛО \n
 */

int main() {
    using namespace std;

    string str = "12345678";
    std::string_view y(str.c_str()+2,3);

    int num = atoi(string(&y[0],  3).c_str());
    cout << num;
    return 0;
}
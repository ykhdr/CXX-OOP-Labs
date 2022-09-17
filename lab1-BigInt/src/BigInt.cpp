#include "BigInt.h"
#include <climits>
#include <algorithm>
#include <valarray>

#define CELL_LIMIT 1000000000
#define MAX_OF_DIGITS 9

int BigInt::countIntLength(int num) {
    int lengthOfNum = 0;
    while (num) {
        num /= 10;
        ++lengthOfNum;
    }
    return lengthOfNum;
}

bool BigInt::isZeroCell(int num) {
    return num == 0;
}

BigInt::BigInt() : sign('+') {
    number.push_back(0);
}

BigInt::BigInt(int num) {
    number.push_back(abs(num));
    (num < 0) ? this->sign = '-' : this->sign = '+';
}

BigInt::BigInt(std::string num) {
    number.push_back(0);
    size_t length = num.size();
    int id = 0;

    {
        int multiplier = CELL_LIMIT / 10;
        bool isSigned = false;
        int i = 0;

        switch (num[0]) {
            case '-':
                sign = '-';
                ++i;
                isSigned = true;
                break;
            case '+':
                sign = '+';
                ++i;
                isSigned = true;
        }

        do {
            if (!multiplier) {
                number.push_back(0);
                ++id;
                multiplier = CELL_LIMIT / 10;
            }

            if (num[i] < '0' || num[i] > '9')
                throw std::invalid_argument("invalid input string");

            number[id] += multiplier * (num[i] - '0');

            multiplier /= 10;
            ++i;

        } while (i < length);

        if (isSigned) {
            --length;
        }
    }

    remainderLength = static_cast<int>(length %= MAX_OF_DIGITS);

    for (int i = 0; i < MAX_OF_DIGITS - remainderLength && remainderLength != 0; ++i)
        number[id] /= 10;

}

BigInt::BigInt(const BigInt &num) : sign(num.sign), number(num.number) {}

BigInt::~BigInt() {
    number.clear();
}

//TODO: понять как сделать
BigInt BigInt::operator~() const {}


/* Сначала нужно посмотреть на последнее число, добавить единицу. Если оно првератилось
 * в CELL_LIMIT, то продолжаем, заполняя нулями это число. Если же у нас число не превариталось
 * в CELL_LIMIT, то просто все сохраняем. Если самое первое число преваритлось в CELL LIMIT,
 * то заменяем ВСЁ число на 1х0.
 *
 * А если перевернуть число? и работать уже с ним.
 * Пробуем
 *
 * */

//TODO: блять пиздец сложно нахуй
BigInt &BigInt::operator++() {

    for (int i = static_cast<int>(number.size() - 1); i >= 0; --i) {
        if (isZeroCell(number[i]))
            continue;

        ++number[i];

        //TODO: упростить
        if (i == number.size() - 1 && countIntLength(number[i]) > remainderLength && remainderLength) {
            number[i] /= static_cast<int>(pow(10, remainderLength + 1));
            continue;
        }

        if (number[i] != CELL_LIMIT) {
            break;
        }

        if (!i) {
            ++remainderLength;
            if (remainderLength == 9) {
                remainderLength = 1;
                number.push_back(0);
            }

            for (int &el: number) {
                el = 0;
            }
            number[0] = CELL_LIMIT / 10;
        }
    }
    return *this;
}

BigInt &BigInt::operator=(const BigInt &num) = default;


BigInt::operator int() const {
    if (number.size() > 1)
        throw std::length_error("Number exceeds int limit");

    int num = number[0];

    if (sign == '-')
        num *= -1;

    return num;
}

BigInt::operator std::string() const {
    std::string str;
    bool isInt = false;
    bool isSignedFirstNumber = false;

    if (size() == 1 && countIntLength(number[0]) < INT_MAX)
        isInt = true;

    if (isInt && isZeroCell(number[0])) {
        return "0";
    }

    if (sign == '-') {
        str += '-';
        isSignedFirstNumber = true;
    }

    for (int i = 0; i < number.size() - 1; ++i) {
        int lengthOnNum = countIntLength(number[i]);

        if (isSignedFirstNumber) {
            ++lengthOnNum;
            isSignedFirstNumber = false;
        }

        for (int j = 0; j < MAX_OF_DIGITS - lengthOnNum; ++j)
            str += '0';

        str.append(std::to_string(number[i]));
    }

    int lastNum = number[number.size() - 1];

    if (isZeroCell(lastNum) && !remainderLength)
        return str;

    if (isZeroCell(lastNum)) {
        for (int i = 0; i < remainderLength; ++i) {
            str += '0';
        }
        return str;
    }

    if (!isInt)
        for (int i = 0; i < (remainderLength - countIntLength(lastNum)) && remainderLength; ++i)
            str += '0';

    str.append(std::to_string(number[number.size() - 1]));

    return str;
}

size_t BigInt::size() const {
    return number.size();
}
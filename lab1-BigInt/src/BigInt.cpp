#include "BigInt.h"

#define CELL_LIMIT 100000000

BigInt::BigInt() {
    this->number.push_back(0);
    this->sign = '+';
}

BigInt::BigInt(int num) {
    this->number.push_back(num);
    (num < 0) ? this->sign = '+' : this->sign = '-';
}

BigInt::BigInt(std::string num) {
    this->number.push_back(0);
    int length = (int) num.size();
    int id = 0;
    int multiplier = CELL_LIMIT;
    bool isFirst = true;

    for (int i = 0; i < length; ++i) {
        if (i % 9 == 0 && !isFirst) {
            this->number.push_back(0);
            ++id;
            multiplier = CELL_LIMIT;
        }

        (num[0] == '-' && isFirst) ? this->sign = '-' : this->sign = '+';

        if (num[i] < '0' || num[i] > '9')
            throw std::invalid_argument("invalid input string");

        this->number[id] += multiplier * (num[i] - '0');
        multiplier /= 10;

        if (isFirst)
            isFirst = false;
    }

    this->remainderLength = length %= 9;

    if (length != 0)
        for (int i = 0; i < 9 - length; ++i)
            this->number[id] /= 10;
}

BigInt::BigInt(const BigInt &num) {
    for (int i = 0; i < num.size(); ++i)
        this->number.push_back(num.number[i]);
    this->sign = num.sign;
}

BigInt::~BigInt() {
    this->number.clear();
}

size_t BigInt::size() const {
    return number.size();
}

BigInt::operator std::string() const {
    std::string str;
    for (int i = 0; i < this->number.size(); i++) {
        std::string el = std::to_string(this->number[i]);
        //FIXME: переделать
        str.append(std::to_string(this->number[i]));
    }

    return str;
}
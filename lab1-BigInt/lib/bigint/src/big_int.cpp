#include "big_int.h"

#include <climits>
#include <algorithm>

namespace {

    constexpr int CELL_LIMIT = 1000000000;
    constexpr int MAX_OF_DIGITS = 9;

}

int BigInt::countIntLength(int num) {
    int lengthOfNum = 0;

    while (num) {
        num /= 10;
        ++lengthOfNum;
    }

    if (lengthOfNum == 0)
        ++lengthOfNum;

    return lengthOfNum;
}

bool BigInt::vctcmp(const std::vector<int32_t> &num1, const std::vector<int32_t> &num2) {
    return std::search(num1.begin(), num1.end(), num2.begin(), num2.end()) != num1.end();
}

void BigInt::removeZeros() {
    while (number_.size() > 1 && number_.back() == 0)
        number_.pop_back();
}

// returns true if str1 > str2
bool BigInt::strCompare(std::string str1, std::string str2) {
    if (str1.size() < str2.size())
        return false;

    if (str1.size() > str2.size())
        return true;

    for (int i = 0; i < str1.size(); ++i) {
        if ((str1[i] - '0') < (str2[i] - '0'))
            return false;
        if ((str1[i] - '0') > (str2[i] - '0'))
            return true;
    }

    return true;
}

BigInt::BigInt() : sign_('+') {
    number_.push_back(0);
}

BigInt::BigInt(int num) {
    if (abs(num) >= CELL_LIMIT) {
        number_.push_back(abs(num) % CELL_LIMIT);
        number_.push_back(abs(num) / CELL_LIMIT);
    } else
        number_.push_back(abs(num));

    (num < 0) ? sign_ = '-' : sign_ = '+';
}

BigInt::BigInt(std::string str) {
    bool isSigned = false;

    if (str.empty())
        throw std::invalid_argument("invalid input string");

    switch (str[0]) {
        case '-':
            sign_ = '-';
            isSigned = true;
            break;
        case '+':
            sign_ = '+';
            isSigned = true;
            break;
        default:
            sign_ = '+';
    }

    if (isSigned)
        str = str.substr(1);

    if (str.empty())
        throw std::invalid_argument("invalid input string");

    for (char el: str)
        if (el < '0' || el > '9')
            throw std::invalid_argument("invalid input string");


    for (int i = str.length(); i > 0; i -= 9) {
        if (i < 9)
            number_.push_back(atoi(str.substr(0, i).c_str()));
        else
            number_.push_back(atoi(str.substr(i - 9, 9).c_str()));
    }

    removeZeros();

    if (number_.back() == 0)
        sign_ = '+';
}

BigInt::BigInt(const BigInt &num) = default;

BigInt::~BigInt() = default;

//TODO: понять как сделать
BigInt BigInt::operator~() const {
    BigInt copy = *this;

    for (int32_t &el: copy.number_) {
        el = ~el;
        el *= -1;
        --el;
    }

    ++copy.number_[0];
    copy.sign_ == '+' ? copy.sign_ = '-' : copy.sign_ = '+';

    copy.removeZeros();
    return copy;
}

BigInt &BigInt::operator++() {
    return (*this += 1);
}

const BigInt BigInt::operator++(int) {
    BigInt tmp = *this;
    ++(*this);

    return tmp;
}

BigInt &BigInt::operator--() {
    return (*this -= 1);
}

const BigInt BigInt::operator--(int) {
    BigInt tmp = *this;
    --(*this);

    return tmp;
}

BigInt &BigInt::operator+=(const BigInt &num) {
    if (sign_ == '-') {
        if (num.sign_ == '-') {
            *this = -*this;
            BigInt tmp = -num;
            *this += tmp;
            *this = -*this;

            return *this;
        }

        *this = -*this;
        *this -= num;
        *this = -*this;

        return *this;
    }

    if (num.sign_ == '-') {
        BigInt tmp = -num;
        *this -= tmp;

        return *this;
    }

    int overLimit = 0;

    for (int i = 0; i < std::max(number_.size(), num.number_.size()) || overLimit != 0; ++i) {

        if (i == number_.size())
            number_.push_back(0);

        number_[i] += overLimit + (i < num.number_.size() ? num.number_[i] : 0);
        overLimit = number_[i] >= CELL_LIMIT;

        if (overLimit != 0)
            number_[i] -= CELL_LIMIT;
    }

    return *this;
}

BigInt &BigInt::operator*=(const BigInt &num) {
    BigInt result;
    result.number_.resize(number_.size() + num.number_.size());

    for (int i = 0; i < number_.size(); ++i) {
        int overLimit = 0;
        for (int j = 0; j < num.number_.size() || overLimit != 0; ++j) {
            long long tmpRes = result.number_[i + j] +
                               number_[i] * 1LL * (j < num.number_.size() ? num.number_[j] : 0) + overLimit;
            result.number_[i + j] = static_cast<int>(tmpRes % CELL_LIMIT);
            overLimit = static_cast<int>(tmpRes / CELL_LIMIT);
        }

    }

    if (sign_ == '-' && num.sign_ == '+')
        result.sign_ = '-';

    if (num.sign_ == '-' && sign_ == '+')
        result.sign_ = '-';

    result.removeZeros();

    *this = result;

    return *this;
}


BigInt &BigInt::operator-=(const BigInt &num) {
    if (num.sign_ == '-') {
        *this += (-num);
        return *this;
    }

    if (sign_ == '-') {
        *this = -*this;
        *this += num;
        *this = -*this;
        return *this;
    }

    if (*this < num) {
        BigInt tmp = (num - *this);
        *this = -tmp;

        return *this;
    }

    int overLimit = 0;

    for (int i = 0; i < num.number_.size() || overLimit; ++i) {
        number_[i] -= overLimit + (i < num.number_.size() ? num.number_[i] : 0);
        overLimit = number_[i] < 0; //ломается из-за uint.

        if (overLimit)
            number_[i] += CELL_LIMIT;
    }

    removeZeros();

    return *this;
}


BigInt &BigInt::operator/=(const BigInt &num2) {
    if (num2.number_.back() == 0)
        throw std::invalid_argument("Division by zero");

    std::string str = static_cast<std::string>(*this);
    std::string str2 = static_cast<std::string>(num2);

    if (str2.size() > str.size())
        return (*this = 0);

    if (str[0] == '-')
        str.erase(0, 1);
    if (str2[0] == '-')
        str2.erase(0, 1);


    bool isNegative = false;

    if (sign_ == '-' && num2.sign_ == '+') {
        isNegative = true;
        sign_ = '+';
    } else if (sign_ == '+' && num2.sign_ == '-')
        isNegative = true;

    BigInt num = num2;
    if (num.sign_ == '-')
        num.sign_ = '+';

    std::string ans;
    std::string dividend;
    std::string divider = str2;
    int zeroesCounter = 0;

    for (char c: str) {
        dividend += c;

        if (dividend == "0") {
            ans += "0";
            dividend.clear();
            continue;
        }

        if (dividend.size() < divider.size()) {
            ++zeroesCounter;
            while (dividend[0] == '0')
                dividend.substr(0, 1);
            continue;
        }

        // dividend - делимое
        // divider - делитель
        // если размер делителя больше -- скип
        //517100700
        //753838384
        int counter = 0;
        std::string prevDivider = "0";
        while (strCompare(dividend, divider)) {
            ++counter;
            BigInt divBI(divider);
            divBI += num;
            prevDivider = divider;
            divider = static_cast<std::string>(divBI);
        }
        BigInt dif(0);
        BigInt dividendBI(dividend);
        BigInt prevDividerBI(prevDivider);
        dif = (dividendBI - prevDividerBI);

        if (dif.number_.back() != 0)
            dividend = static_cast<std::string>(dif);
        else
            dividend = "";

        divider = str2;
        for (int i = 0; i < zeroesCounter; ++i) {
            ans += "0";
        }
        zeroesCounter = 0;
        ans += std::to_string(counter);
    }

    for (int i = 0; i < zeroesCounter; ++i) {
        ans += '0';
    }

    *this = BigInt(ans);
    removeZeros();

    if (isNegative)
        sign_ = '-';

    return *this;
}

BigInt &BigInt::operator^=(const BigInt &num) {
    for (int i = 0; i < std::min(number_.size(), num.number_.size()); ++i) {
        number_[i] = number_[i] ^ num.number_[i];
    }
    if (sign_ == '-')
        num.sign_ == '+' ? sign_ = '-' : sign_ = '+';
    else
        num.sign_ == '-' ? sign_ = '-' : sign_ = '+';

    removeZeros();

    return *this;
}

BigInt &BigInt::operator%=(const BigInt &num) { // переделать
    BigInt q = (*this / num);
    BigInt s = q * num;
    BigInt res = *this - s;

    if (res.sign_ == '-')
        res += num;

    *this = res;

    return *this;
}

BigInt &BigInt::operator&=(const BigInt &num) {
    for (int i = 0; i < std::min(number_.size(), num.number_.size()); ++i) {
        number_[i] = number_[i] & num.number_[i];
    }

    if (sign_ == '-')
        num.sign_ == '-' ? sign_ = '-' : sign_ = '+';
    else
        sign_ = '+';

    removeZeros();

    return *this;

}

BigInt &BigInt::operator|=(const BigInt &num) {
    for (int i = 0; i < std::min(number_.size(), num.number_.size()); ++i) {
        number_[i] = number_[i] | num.number_[i];
    }

    if (sign_ == '+')
        num.sign_ == '-' ? sign_ = '-' : sign_ = '+';

    removeZeros();

    return *this;
}

BigInt &BigInt::operator=(const BigInt &num) {
    if (this == &num)
        return *this;

    number_ = num.number_;
    sign_ = num.sign_;

    return *this;
};

BigInt BigInt::operator+() const {
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt copy(*this);
    copy.sign_ == '-' ? copy.sign_ = '+' : copy.sign_ = '-';

    return copy;
}

bool BigInt::operator==(const BigInt &num) const {
    if (sign_ != num.sign_)
        return false;

    if (number_.size() != num.number_.size())
        return false;

    if (!vctcmp(number_, num.number_))
        return false;

    return true;
}

bool BigInt::operator!=(const BigInt &num) const {
    return !operator==(num);
}

bool BigInt::operator<(const BigInt &num) const {
    if (sign_ < num.sign_) // '-' - 55, '+' - 53
        return false;

    if (sign_ > num.sign_)
        return true;

    if (number_.size() > num.number_.size()) {
        if (sign_ == '+')
            return false;
        else
            return true;
    }

    if (number_.size() < num.number_.size()) {
        if (sign_ == '+')
            return true;
        else
            return false;
    }

    if (vctcmp(number_, num.number_)) // maybe to delete
        return false;

    bool isBigger = false;
    for (int i = 0; i < number_.size(); ++i) {
        if (number_[i] > num.number_[i]) {
            isBigger = true;
            break;
        }
    }

    if (isBigger) {
        if (sign_ == '+')
            return false;
        else
            return true;
    }

    if (sign_ == '+')
        return true;
    else
        return false;
}

bool BigInt::operator>(const BigInt &num) const {
    if (vctcmp(number_, num.number_))
        return false;
    return !operator<(num);
}

bool BigInt::operator<=(const BigInt &num) const {
    if (sign_ == num.sign_ && vctcmp(number_, num.number_))
        return true;

    return operator<(num);
}

bool BigInt::operator>=(const BigInt &num) const {
    if (sign_ == num.sign_ && vctcmp(number_, num.number_))
        return true;

    return operator>(num);
}

BigInt::operator int() const {
    if (number_.size() > 1 && number_.back() > 2)
        throw std::length_error("Number exceeds int limit");

    long long num = 0;

    if (number_.size() > 1) {
        num = number_[0] + number_[1] * CELL_LIMIT;
        if (sign_ == '+') {
            if (num > INT32_MAX)
                throw std::length_error("Number exceeds int limit");
        } else if (num > (INT32_MAX + 1LL))
            throw std::length_error("Number exceeds int limit");
    } else
        num = number_[0];

    if (sign_ == '-')
        num *= -1;

    return static_cast<int>(num);
}


BigInt::operator std::string() const {
    std::string str;

    if (sign_ == '-')
        str += '-';

    str.append(std::to_string(number_[number_.size() - 1]));

    for (int i = number_.size() - 2; i >= 0; --i) {
        int lengthOnNum = countIntLength(number_[i]);

        for (int j = 0; j < MAX_OF_DIGITS - lengthOnNum; ++j)
            str += '0';

        str.append(std::to_string(number_[i]));
    }

    return str;
}

size_t BigInt::size() const {
    return (sizeof(int) * number_.size() + 1);
}


BigInt operator+(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp += num2;

    return tmp;
}

BigInt operator-(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp -= num2;

    return tmp;
}

BigInt operator*(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp *= num2;

    return tmp;
}

BigInt operator/(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp /= num2;

    return tmp;
}

BigInt operator^(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp ^= num2;

    return tmp;
}

BigInt operator%(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp %= num2;

    return tmp;
}

BigInt operator&(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp &= num2;

    return tmp;
}

BigInt operator|(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp |= num2;

    return tmp;
}

std::ostream &operator<<(std::ostream &out, const BigInt &num) {
    out << static_cast<std::string>(num);

    return out;
}
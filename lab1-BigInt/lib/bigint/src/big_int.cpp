#include "big_int.h"

#include <climits>
#include <algorithm>


#define CELL_LIMIT 1000000000
#define MAX_OF_DIGITS 9

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

bool BigInt::vctcmp(const std::vector<int> &bigger, const std::vector<int> &smaller) {
    return std::search(bigger.begin(), bigger.end(), smaller.begin(), smaller.end()) != bigger.end();
}

void BigInt::removeZeros() {
    while (number_.back() == 0 && number_.size() > 1)
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
    if (num >= CELL_LIMIT) {
        number_.push_back(abs(num) % CELL_LIMIT);
        number_.push_back(abs(num) / CELL_LIMIT);
    } else
        number_.push_back(abs(num));

    (num < 0) ? this->sign_ = '-' : this->sign_ = '+';
}

BigInt::BigInt(std::string str) {
    bool isSigned = false;

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
    
    if(str.empty())
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

    if(number_.back()==0)
        sign_ = '+';
}

BigInt::BigInt(const BigInt &num) = default;

BigInt::~BigInt() {
    number_.clear();
}

//TODO: понять как сделать
BigInt BigInt::operator~() const {
    BigInt copy = *this;

    for (int el: copy.number_) {
        el = ~el;
        el *= -1;
    }

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
    if (this->sign_ == '-') {
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

    for (int i = 0; i < std::max(this->number_.size(), num.number_.size()) || overLimit != 0; ++i) {

        if (i == this->number_.size())
            this->number_.push_back(0);

        this->number_[i] += overLimit + (i < num.number_.size() ? num.number_[i] : 0);
        overLimit = this->number_[i] >= CELL_LIMIT;

        if (overLimit != 0)
            this->number_[i] -= CELL_LIMIT;
    }

    return *this;
}

BigInt &BigInt::operator*=(const BigInt &num) {
    BigInt result;
    result.number_.resize(this->number_.size() + num.number_.size());

    for (int i = 0; i < this->number_.size(); ++i) {
        int overLimit = 0;
        for (int j = 0; j < num.number_.size() || overLimit != 0; ++j) {
            long long tmpRes = result.number_[i + j] +
                               this->number_[i] * 1LL * (j < num.number_.size() ? num.number_[j] : 0) + overLimit;
            result.number_[i + j] = static_cast<int>(tmpRes % CELL_LIMIT);
            overLimit = static_cast<int>(tmpRes / CELL_LIMIT);
        }

    }

    if (this->sign_ == '-' && num.sign_ == '+')
        result.sign_ = '-';

    if (num.sign_ == '-' && this->sign_ == '+')
        result.sign_ = '-';

    result.removeZeros();

    this->number_.clear();

    *this = result;

    return *this;
}


BigInt &BigInt::operator-=(const BigInt &num) {
    if (num.sign_ == '-') {
        *this += (-num);
        return *this;
    }

    if (this->sign_ == '-') {
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
        this->number_[i] -= overLimit + (i < num.number_.size() ? num.number_[i] : 0);
        overLimit = this->number_[i] < 0;

        if (overLimit)
            this->number_[i] += CELL_LIMIT;
    }

    removeZeros();

    return *this;
}


BigInt &BigInt::operator/=(const BigInt &num2) { //TODO: придумать решение
    if (num2.number_.back() == 0)
        throw std::invalid_argument("Division by zero");

    if (this->number_.back() == 0) //maybe to delete
        return *this;

    std::string str = static_cast<std::string>(*this);
    std::string str2 = static_cast<std::string>(num2);

    if (str2.size() > str.size())
        return (*this = 0);

    if (str[0] == '-')
        str.erase(0, 1);
    if (str2[0] == '-')
        str2.erase(0, 1);


    bool isNegative = false;

    if (this->sign_ == '-' && num2.sign_ == '+') {
        isNegative = true;
        this->sign_ = '+';
    } else if (this->sign_ == '+' && num2.sign_ == '-')
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
        dif = (dividendBI -= prevDividerBI);

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
        this->sign_ = '-';

    return *this;
}

BigInt &BigInt::operator^=(const BigInt &num) {
    for (int i = 0; i < std::min(this->number_.size(), num.number_.size()); ++i) {
        this->number_[i] = this->number_[i] ^ num.number_[i];
    }
    if (this->sign_ == '-')
        num.sign_ == '+' ? this->sign_ = '-' : this->sign_ = '+';
    else
        num.sign_ == '-' ? this->sign_ = '-' : this->sign_ = '+';

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
    for (int i = 0; i < std::min(this->number_.size(), num.number_.size()); ++i) {
        this->number_[i] = this->number_[i] & num.number_[i];
    }

    if (this->sign_ == '-')
        num.sign_ == '-' ? this->sign_ = '-' : this->sign_ = '+';
    else
        this->sign_ = '+';

    removeZeros();

    return *this;

}

BigInt &BigInt::operator|=(const BigInt &num) {
    for (int i = 0; i < std::min(this->number_.size(), num.number_.size()); ++i) {
        this->number_[i] = this->number_[i] | num.number_[i];
    }

    if (this->sign_ == '+')
        num.sign_ == '-' ? this->sign_ = '-' : this->sign_ = '+';

    removeZeros();

    return *this;
}

BigInt &BigInt::operator=(const BigInt &num) {
    if (this == &num)
        return *this;

    this->number_ = num.number_;
    this->sign_ = num.sign_;

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
    if(vctcmp(number_,num.number_))
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
    if (number_.size() > 1)
        throw std::length_error("Number exceeds int limit");

    int num = number_[0];

    if (sign_ == '-')
        num *= -1;

    return num;
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
    return sizeof(int)*number_.size();
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

std::ostream &operator<<(std::ostream &out, const BigInt &num){
    out << static_cast<std::string>(num);
    return out;
}
#pragma once

#include <vector>
#include <ostream>

#include <cstdint>

class BigInt {

private:
    std::vector<int32_t> number_;
    bool isNegative_ = false;

    static int countIntLength(int);

    void removeZeros();
    bool strCompare(std::string,std::string);

public:
    BigInt();

    BigInt(int);

    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке

    BigInt(const BigInt &);

    ~BigInt();

    BigInt &operator=(const BigInt &);  //возможно присваивание самому себе!

    BigInt operator~() const; // побитовый оператор не

    BigInt &operator++();

    const BigInt operator++(int);

    BigInt &operator--();

    const BigInt operator--(int);

    BigInt &operator+=(const BigInt &);

    BigInt &operator*=(const BigInt &);

    BigInt &operator-=(const BigInt &);

    BigInt &operator/=(const BigInt &);

    BigInt &operator^=(const BigInt &); // xor

    BigInt &operator%=(const BigInt &);

    BigInt &operator&=(const BigInt &);

    BigInt &operator|=(const BigInt &);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt &) const;

    bool operator!=(const BigInt &) const;

    bool operator<(const BigInt &) const;

    bool operator>(const BigInt &) const;

    bool operator<=(const BigInt &) const;

    bool operator>=(const BigInt &) const;

    operator int() const;

    operator std::string() const;

    size_t size() const;  // size in bytes


};

BigInt operator+(const BigInt &, const BigInt &);

BigInt operator-(const BigInt &, const BigInt &);

BigInt operator*(const BigInt &, const BigInt &);

BigInt operator/(const BigInt &, const BigInt &);

BigInt operator^(const BigInt &, const BigInt &); // xor

BigInt operator%(const BigInt &, const BigInt &);

BigInt operator&(const BigInt &, const BigInt &);

BigInt operator|(const BigInt &, const BigInt &);


std::ostream &operator<<(std::ostream &o, const BigInt &i);

#pragma once

#include <vector>
#include <ostream>


class big_int {

private:
    std::vector<int> number_;
    char sign_ = '+';

    static int countIntLength(int);
    static bool vctcmp(const std::vector<int> &, const std::vector<int> &);

    void removeZeros();
    bool strCompare(std::string,std::string);

public:
    big_int();

    big_int(int);

    big_int(std::string); // бросать исключение std::invalid_argument при ошибке

    big_int(const big_int &);

    ~big_int();

    big_int &operator=(const big_int &);  //возможно присваивание самому себе!

    big_int operator~() const; // побитовый оператор не

    big_int &operator++();

    const big_int operator++(int) const;

    big_int &operator--();

    const big_int operator--(int) const;

    big_int &operator+=(const big_int &);

    big_int &operator*=(const big_int &);

    big_int &operator-=(const big_int &);

    big_int &operator/=(const big_int &);

    big_int &operator^=(const big_int &); // xor

    big_int &operator%=(const big_int &);

    big_int &operator&=(const big_int &);

    big_int &operator|=(const big_int &);

    big_int operator+() const;  // unary +
    big_int operator-() const;  // unary -

    bool operator==(const big_int &) const;

    bool operator!=(const big_int &) const;

    bool operator<(const big_int &) const;

    bool operator>(const big_int &) const;

    bool operator<=(const big_int &) const;

    bool operator>=(const big_int &) const;

    operator int() const;

    operator std::string() const;

    size_t size() const;  // size in bytes


};

big_int operator+(const big_int &, const big_int &);

big_int operator-(const big_int &, const big_int &);

big_int operator*(const big_int &, const big_int &);

big_int operator/(const big_int &, const big_int &);

big_int operator^(const big_int &, const big_int &); // xor

big_int operator%(const big_int &, const big_int &);

big_int operator&(const big_int &, const big_int &);

big_int operator|(const big_int &, const big_int &);


std::ostream &operator<<(std::ostream &o, const big_int &i);

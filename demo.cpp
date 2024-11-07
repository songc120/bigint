#include <iostream>
#include <vector>
#include "bigint.hpp"

bigint::bigint()
{
    digits.push_back(int8_t(0));
    is_negative = false;
}
bigint::bigint(int64_t n)
{
    if (n < 0)
    {
        is_negative = true;
        n = -n;
    }
    else
    {
        is_negative = false;
    }
    while (n)
    {
        digits.push_back(n % 10);
        n /= 10;
    }
    std::reverse(digits.begin(), digits.end());
}
bigint::bigint(std::string n)
{
    if (n[0] == '-')
    {
        is_negative = true;
        n = n.substr(1);
    }
    else
    {
        is_negative = false;
    }
    for (char ch : n)
    {
        digits.push_back(ch - '0');
    }
}
bigint::bigint(const bigint &other) : digits(other.digits), is_negative(other.is_negative) {}

bigint bigint::operator-() const
{
    bigint flip = *this;
    flip.is_negative = !is_negative;

    return flip;
}

bool bigint::operator==(bigint const &other) const
{
    if (is_negative == other.is_negative && digits == other.digits)
        return true;
    else
        return false;
}

bool bigint::operator!=(bigint const &other) const
{
    if (is_negative != other.is_negative || digits != other.digits)
        return true;
    else
        return false;
}

bool bigint::operator<(bigint const &other) const
{
    if (*this == other)
        return false;
    else if (is_negative != other.is_negative)
        return is_negative;
    else if (digits.size() == other.digits.size())
    {
        for (uint64_t i = 0; i < digits.size(); i++)
        {
            if (digits[i] != other.digits[i])
                return digits[i] > other.digits[i] ? is_negative : !is_negative;
        }
        return false;
    }
    else if (digits.size() > other.digits.size())
    {
        return is_negative;
    }
    else
        return !is_negative;
}

bool bigint::operator>(bigint const &other) const
{
    return other < *this;
}
bool bigint::operator<=(bigint const &other) const
{
    return other == *this || other < *this;
}
bool bigint::operator>=(bigint const &other) const
{
    return other == *this || other > *this;
}

bigint &bigint::operator=(const bigint &other)
{
    is_negative = other.is_negative;
    digits = other.digits;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    if (n.is_negative)
    {
        os << '-';
    }
    for (int8_t digit : n.digits)
    {
        os << static_cast<int16_t>(digit);
    }
    return os;
}

int main()
{
    std::string str = "1234567890";
    bigint str_big_int(str);
    std::cout << "The bigint from string is " << str_big_int << ".\n";

    bigint default_big_int;
    std::cout << "The default bigint is " << default_big_int << ".\n";

    int64_t int64(1234567890);
    bigint int_big_int(int64);
    std::cout << "The bigint from int is " << int_big_int << ".\n";

    std::string str_neg = "-1234567890";
    bigint str_big_int_neg(str_neg);
    std::cout << "The bigint from string is " << str_big_int_neg << ".\n";

    int64_t int64_neg(-1234567890);
    bigint int_big_int_neg(int64_neg);
    std::cout << "The bigint from int is " << int_big_int_neg << ".\n";

    bigint neg = -int_big_int_neg;
    std::cout
        << "The -(-c) " << neg << ".\n";

    bigint neg1 = -int_big_int;
    std::cout
        << "The -(1234567890) " << neg1 << ".\n";

    bigint neg2 = -default_big_int;
    std::cout
        << "The -(default) " << neg2 << ".\n";

    if (neg2 == int_big_int)
    {
        std::cout
            << "neg2 ==  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    }
    else
    {
        std::cout
            << "neg2 !=  int_big_int " << ".\n";
    }

    if (neg2 != int_big_int)
    {
        std::cout
            << "neg2 !=  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    }
    else
    {
        std::cout
            << "neg2 ==  int_big_int " << ".\n";
    }

    neg2 = int_big_int;
    std::cout
        << "assign neg2 to  int_big_int " << neg2 << ".\n";

    if (neg2 == int_big_int)
    {
        std::cout
            << "neg2 ==  int_big_int " << ".\n";
    }
    else
    {
        std::cout
            << "neg2 !=  int_big_int " << ".\n";
    }

    if (neg2 != int_big_int)
    {
        std::cout
            << "neg2 !=  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    }
    else
    {
        std::cout
            << "neg2 ==  int_big_int " << ".\n";
    }

    bigint smallpos = bigint(123);
    bigint bigpos = bigint(12345);
    bigint bigbigpos = bigint(13345);
    bigint nsmallpos = bigint(-123);
    bigint nbigpos = bigint(-12345);
    bigint nbigbigpos = bigint(-13345);

    if (smallpos <= bigpos)
        printf("smallpos > bigpos\n");
    if (bigpos <= bigbigpos)
        printf("bigpos > bigbigpos\n");
    if (nbigpos <= nsmallpos)
        printf("nbigpos > nsmallpos\n");
    if (nbigbigpos <= nbigpos)
        printf("nbigbigpos > nbigpos\n");

    if (nsmallpos <= bigpos)
        printf("nsmallpos > bigpos\n");
    if (nsmallpos <= nsmallpos)
        printf("F:nsmallpos > nsmallpos\n");
    if (nsmallpos <= nbigpos)
        printf("F:nsmallpos > nbigpos\n");
    if (nsmallpos <= nbigpos)
        printf("F:nsmallpos > nbigpos\n");
    return 0;
}
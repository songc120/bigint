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

    return 0;
}
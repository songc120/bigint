#include <iostream>
#include <vector>
#include "bigint.hpp"
#include <stdint.h>

bigint::bigint()
{
    digits.push_back(0);
}
bigint::bigint(int8_t n)
{
    while (n)
    {
        digits.push_back(n % 10);
        n /= 10;
    }
}
bigint::bigint(std::string n)
{
    for (char ch : n)
    {
        digits.push_back(ch - '0');
    }
}

std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    for (int8_t digit : n.digits)
    {
        os << static_cast<int>(digit);
    }
    return os;
}

int main()
{
    std::string str = "123456789";
    bigint str_big_int(str);
    std::cout << "The bigint from string is " << str_big_int << ".\n";

    return 0;
}
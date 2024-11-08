#include <iostream>
#include <vector>
#include "bigint.hpp"

bigint::bigint()
{
    digits.push_back(uint8_t(0));
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
        digits.push_back(static_cast<uint8_t>(n % 10));
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
        digits.push_back(static_cast<uint8_t>(ch - '0'));
    }
}
bigint::bigint(const bigint &other) : digits(other.digits), is_negative(other.is_negative) {}

uint8_t bigint::get_digit(bigint const &big_num, const uint64_t n) const
{
    return n < 0 ? static_cast<uint8_t>(0) : big_num.digits[n];
}

bigint bigint::operator+(bigint const &other) const
{
    bigint sum;
    
    if (is_negative == other.is_negative){
        uint8_t carry = 0;
        size_t this_len = digits.size();
        size_t other_len = other.digits.size();
        size_t len = std::max(this_len, other_len);

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t sum_i = get_digit(*this, this_len - 1 - i) + other.get_digit(other, other_len - 1 - i) + carry;
            carry = sum_i / 10;
            sum.digits.insert(sum.digits.begin(), static_cast<uint8_t>(sum_i % 10));
        }
        if (carry > 0)
            sum.digits.insert(sum.digits.begin(), static_cast<uint8_t>(carry));
        
        sum.is_negative = is_negative;
        sum.digits.pop_back();
    }
    else if (is_negative){
        sum = -(-*this - other);
    } else sum = *this- (-other);

    return sum;
}

bigint bigint::operator-(bigint const &other) const{
    bigint diff;
    
    if (is_negative == other.is_negative){
        diff.is_negative = *this >= other ? 0 : 1;

        bigint pos_num;
        bigint neg_num;

        if (abs()> other.abs()) {
            pos_num = *this;
            neg_num = other;
        } else {
            pos_num = other;
            neg_num = *this;
        }

        size_t pos_len = pos_num.digits.size();
        size_t neg_len = neg_num.digits.size();
        size_t len = std::max(pos_len, neg_len);

        uint8_t borrow = 0;

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t pos_i = get_digit(pos_num, pos_len - 1 - i);
            uint8_t neg_i = get_digit(neg_num, neg_len - 1 - i);
            uint8_t diff_i;
            
            if (pos_i < (neg_i+borrow))
            {
                diff_i = neg_i - pos_i + borrow;
                borrow = 1;
                diff_i = static_cast<uint8_t>(10) - diff_i;
            }
            else
            {
                diff_i = pos_i - neg_i - borrow;
                borrow = 0;
            }
            diff.digits.insert(diff.digits.begin(), diff_i);
        }

        diff.digits.pop_back();
        uint64_t max_zero_iter = diff.digits.size() - 1;
        for (uint64_t j = 0; j < max_zero_iter; j ++){
            if (diff.digits[0] == 0) {
                diff.digits.erase(diff.digits.begin());}
            else break;
        }

    } else if (is_negative){
        diff = -(-*this + other);
    } else diff = *this+ (-other);
    return diff;

}

bigint bigint::operator-() const
{
    bigint flip = *this;
    flip.is_negative = !is_negative;

    return flip;
}

bigint bigint::abs() const{
    bigint abs = *this;
    abs.is_negative = 0;

    return abs;
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
    return other == *this || *this < other;
}
bool bigint::operator>=(bigint const &other) const
{
    return other == *this || *this > other;
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
    for (uint8_t digit : n.digits)
    {
        os << static_cast<uint16_t>(digit);
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

    // if (neg2 == int_big_int)
    // {
    //     std::cout
    //         << "neg2 ==  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    // }
    // else
    // {
    //     std::cout
    //         << "neg2 !=  int_big_int " << ".\n";
    // }

    // if (neg2 != int_big_int)
    // {
    //     std::cout
    //         << "neg2 !=  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    // }
    // else
    // {
    //     std::cout
    //         << "neg2 ==  int_big_int " << ".\n";
    // }

    // neg2 = int_big_int;
    // std::cout
    //     << "assign neg2 to  int_big_int " << neg2 << ".\n";

    // if (neg2 == int_big_int)
    // {
    //     std::cout
    //         << "neg2 ==  int_big_int " << ".\n";
    // }
    // else
    // {
    //     std::cout
    //         << "neg2 !=  int_big_int " << ".\n";
    // }

    // if (neg2 != int_big_int)
    // {
    //     std::cout
    //         << "neg2 !=  int_big_int " << neg2 << ";" << int_big_int << ".\n";
    // }
    // else
    // {
    //     std::cout
    //         << "neg2 ==  int_big_int " << ".\n";
    // }

    bigint smallpos = bigint(123);
    bigint smallpos2 = bigint(923);
    bigint bigpos = bigint(12345);
    bigint bigbigpos = bigint(13345);
    bigint nsmallpos = bigint(-923);
    bigint nbigpos = bigint(-12345);
    bigint nbigbigpos = bigint(-13345);

    // if (smallpos <= bigpos)
    //     printf("smallpos > bigpos\n");
    // if (bigpos <= bigbigpos)
    //     printf("bigpos > bigbigpos\n");
    // if (nbigpos <= nsmallpos)
    //     printf("nbigpos > nsmallpos\n");
    // if (nbigbigpos <= nbigpos)
    //     printf("nbigbigpos > nbigpos\n");

    // if (nsmallpos <= bigpos)
    //     printf("nsmallpos > bigpos\n");
    // if (nsmallpos <= nsmallpos)
    //     printf("F:nsmallpos > nsmallpos\n");
    // if (nsmallpos <= nbigpos)
    //     printf("F:nsmallpos > nbigpos\n");
    // if (nsmallpos <= nbigpos)
    //     printf("F:nsmallpos > nbigpos\n");

    std::cout << "-----plus------.\n";
    std::cout
        << 123 + 12345 << " = " << smallpos + bigpos << ".\n";

    std::cout << "-----plus------.\n";
    std::cout
        << -923 -12345 << " = " << nsmallpos + nbigpos << ".\n";
    
    std::cout << "----plus-------.\n";
    std::cout
        << 0 << "  = " << default_big_int + default_big_int << ".\n";
    std::cout << "----plus-------.\n";
    std::cout
        << 12345 << " + " << -923 << "=" << 12345 - 923 << "  = " << bigpos + bigint(-923)<< ".\n";
    std::cout << "----plus-------.\n";
    std::cout
        << 291 << " + " <<- 92 << "=" << 291 - 92 << "  = " << bigint(291) + bigint(-92)<< ".\n";

    std::cout << "-----plus------.\n";
    std::cout
        << smallpos << " - " << bigpos << "=" << 123 - 12345 << "  = " << smallpos + (-bigpos) << ".\n";

    std::cout << "-----plus------.\n";
    std::cout
        << -2000 << " + " << 1 << "=" << -2000 + 1 << "  = " << bigint(-2000) + bigint(1) << ".\n";

    // std::cout << "----minus-------.\n";
    // std::cout
    //     << bigpos << " - " << smallpos2 << "=" << 12345 - 923 << "  = " << bigpos - smallpos2<< ".\n";

    // std::cout << "-----minus------.\n";
    // std::cout
    //     << bigbigpos << " - " << bigpos << "=" << 13345 - 12345 << "  = " << bigbigpos - bigpos<< ".\n";

    // std::cout << "------minus-----.\n";
    // std::cout
    //     << 291 << " - " << 92 << "=" << 291 - 92 << " = " << bigint(291) -bigint(92) << ".\n";

    // std::cout << "------minus-----.\n";
    // std::cout
    //     << 7000 << " - " << 5023 << "=" << 7000 - 5023 << "  = " << bigint(7000) -bigint(5023) << ".\n";
    
    // std::cout << "------minus-----.\n";
    // std::cout
    //     << 100000 << " - " << 99999 << "=" << 100000 - 99999 << " = " << bigint(100000) -bigint(99999) << ".\n";
    //     std::cout << "------minus-----.\n";
    // std::cout
    //     << 100000 << " - " << 100000 << "=" << 100000 - 100000 << " = " << bigint(100000) -bigint(100000) << ".\n";
    
    
    // std::cout << "------minus-----.\n";
    // std::cout
    //     << nsmallpos << " - " << nbigpos << "=" << -923 - -12345 << "  = " << nsmallpos -nbigpos << ".\n";

    // std::cout << "------minus-----.\n";
    // std::cout
    //     << 11 << " - " << -99 << "=" << 11 - -99 << "  = " << bigint(11) -bigint(-99) << ".\n";

    // std::cout << "------minus-----.\n";
    // std::cout
    //     << -11 << " - " << 99 << "=" << -11 - 99 << "  = " << bigint(-11) -bigint(99) << ".\n";
    return 0;
    
}
#include <iostream>
#include <vector>
#include "bigint.hpp"

bigint::bigint()
{
    push_back(uint8_t(0));
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
        push_back(static_cast<uint8_t>(n % 10));
        n /= 10;
    }
    std::reverse(begin(), end());
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
        push_back(static_cast<uint8_t>(ch - '0'));
    }
}
bigint::bigint(const bigint &other) : digits(other.digits), is_negative(other.is_negative) {}
//helpers

uint8_t bigint::get_digit(const uint64_t n) const
{
    return n < 0 ? static_cast<uint8_t>(0) : digits[n];
}

bigint bigint::push_back(const uint8_t n){
    digits.push_back(n);
    return *this;
}

bigint bigint::pop_back(){
    digits.pop_back();
    return *this;
}

std::vector<uint8_t>::iterator bigint::begin(){
    return digits.begin();
}

std::vector<uint8_t>::iterator bigint::end(){
    return digits.end();
}

bigint bigint::insert(std::vector<uint8_t>::iterator ind,const uint8_t num){
    digits.insert(ind, num);
    return *this;
}

bigint bigint::erase(const std::vector<uint8_t>::iterator ind){
    digits.erase(ind);
    return *this;
}

size_t bigint::size() const{
    return digits.size();
}

bool bigint::get_is_negative() const{
    return is_negative;
}

bigint bigint::set_negative(bool neg){
    is_negative = neg;
    return *this;
}

//overloaded operators
bigint bigint::operator+(bigint const &other) const
{
    bigint sum;
    
    if (get_is_negative() == other.get_is_negative()){
        uint8_t carry = 0;
        size_t this_len = size();
        size_t other_len = other.size();
        size_t len = std::max(this_len, other_len);

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t sum_i = get_digit(this_len - 1 - i) + other.get_digit(other_len - 1 - i) + carry;
            carry = sum_i / 10;
            sum.insert(sum.begin(), static_cast<uint8_t>(sum_i % 10));
        }
        if (carry > 0)
            sum.insert(sum.begin(), static_cast<uint8_t>(carry));
        
        sum.set_negative(get_is_negative());
        sum.pop_back();
    }
    else if (get_is_negative()){
        sum = -(-*this - other);
    } else sum = *this- (-other);

    return sum;
}

bigint bigint::operator+=(bigint const &increment){
    *this = *this + increment;
    return *this;
}

bigint bigint::operator-(bigint const &other) const{
    bigint diff;
    
    if (get_is_negative() == other.get_is_negative()){
        diff.set_negative(*this >= other ? 0 : 1);

        bigint pos_num;
        bigint neg_num;

        if (abs()> other.abs()) {
            pos_num = *this;
            neg_num = other;
        } else {
            pos_num = other;
            neg_num = *this;
        }

        size_t pos_len = pos_num.size();
        size_t neg_len = neg_num.size();
        size_t len = std::max(pos_len, neg_len);

        uint8_t borrow = 0;

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t pos_i = pos_num.get_digit(pos_len - 1 - i);
            uint8_t neg_i = neg_num.get_digit(neg_len - 1 - i);
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
            diff.insert(diff.begin(), diff_i);
        }

        diff.pop_back();
        uint64_t max_zero_iter = diff.size() - 1;
        for (uint64_t j = 0; j < max_zero_iter; j ++){
            if (diff.get_digit(0) == 0) {
                diff.erase(diff.begin());}
            else break;
        }

    } else if (get_is_negative()){
        diff = -(-*this + other);
    } else diff = *this+ (-other);
    return diff;

}

bigint bigint::operator-=(bigint const &increment){
    *this = *this - increment;
    return *this;
}

bigint bigint::operator*(bigint const &other) const
{
    bigint prod;

    if (abs() == prod || other.abs() == prod) return prod;
    bigint short_num;
    bigint long_num;

    if (abs()> other.abs()) {
        long_num = *this;
        short_num = other;
    } else {
        long_num = other;
        short_num = *this;
    }

    uint8_t carry = 0;
    size_t long_iter = long_num.size();
    size_t short_iter = short_num.size();

    for (uint64_t i = 0; i < short_iter; i++){
        bigint digits_i;
        for (uint64_t j = 0; j < long_iter; j++){
            uint8_t prod_i = short_num.get_digit(short_iter - 1 - i) * long_num.get_digit(long_iter - 1 - j) + carry;
            carry = prod_i / 10;
            digits_i.insert(digits_i.begin(), static_cast<uint8_t>(prod_i % 10));
            // std::cout << "\n digit at i = "<< i << " j = "<<j<<" is: " << prod_i % 10 << "\n";
            // std::cout << "\n carry at i = "<< i << " j = "<<j<<" is: " << static_cast<uint16_t>(carry) << "\n";
        }
        for (uint8_t k = 0; k < i; k++) digits_i.push_back(0);
        digits_i.pop_back();
        prod += digits_i;
        // std::cout << "\n digits_i at i = "<< i << " is:"<< digits_i<<"\n";
        // std::cout << "\n prod at i = "<< i << " is:"<< prod<<"\n";
    }

    if (carry > 0)
        prod.insert(prod.begin(), static_cast<uint8_t>(carry));
    
    prod.set_negative(!(get_is_negative() == other.get_is_negative()));
    return prod;
}

bigint bigint::operator-() const
{
    bigint flip = *this;
    flip.set_negative(!get_is_negative());

    return flip;
}

bigint bigint::abs() const{
    bigint abs = *this;
    abs.set_negative(0);

    return abs;
}

bool bigint::operator==(bigint const &other) const
{
    if (get_is_negative() == other.get_is_negative() && digits == other.digits)
        return true;
    else
        return false;
}

bool bigint::operator!=(bigint const &other) const
{
    if (get_is_negative() != other.get_is_negative() || digits != other.digits)
        return true;
    else
        return false;
}

bool bigint::operator<(bigint const &other) const
{
    if (*this == other)
        return false;
    else if (get_is_negative() != other.get_is_negative())
        return get_is_negative();
    else if (size() == other.size())
    {
        for (uint64_t i = 0; i < size(); i++)
        {
            if (get_digit(i) != other.get_digit(i))
                return get_digit(i) > other.get_digit(i) ? get_is_negative() : !get_is_negative();
        }
        return false;
    }
    else if (size() > other.size())
    {
        return get_is_negative();
    }
    else
        return !get_is_negative();
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
    set_negative(other.get_is_negative());
    digits = other.digits;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    if (n.get_is_negative())
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
        << smallpos << " + " << bigpos << "="<< 123 + 12345 << " = " << smallpos + bigpos << ".\n";

    std::cout << smallpos << ".\n";



    std::cout << "-----plus------.\n";
    std::cout
        << nsmallpos << " + " << nbigpos << "="<< -923 -12345 << " = " << nsmallpos + nbigpos << ".\n";
    
    std::cout << "----plus-------.\n";
    std::cout
        << default_big_int << " + " << default_big_int << "="<< 0 << "  = " << default_big_int + default_big_int << ".\n";
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

    std::cout << "----minus-------.\n";
    std::cout
        << bigpos << " - " << smallpos2 << "=" << 12345 - 923 << "  = " << bigpos - smallpos2<< ".\n";

    std::cout << bigpos << ".\n";

    std::cout << "-----minus------.\n";
    std::cout
        << bigbigpos << " - " << bigpos << "=" << 13345 - 12345 << "  = " << bigbigpos - bigpos<< ".\n";

    std::cout << "------minus-----.\n";
    std::cout
        << 291 << " - " << 92 << "=" << 291 - 92 << " = " << bigint(291) -bigint(92) << ".\n";

    std::cout << "------minus-----.\n";
    std::cout
        << 7000 << " - " << 5023 << "=" << 7000 - 5023 << "  = " << bigint(7000) -bigint(5023) << ".\n";
    
    std::cout << "------minus-----.\n";
    std::cout
        << 100000 << " - " << 99999 << "=" << 100000 - 99999 << " = " << bigint(100000) -bigint(99999) << ".\n";
        std::cout << "------minus-----.\n";
    std::cout
        << 100000 << " - " << 100000 << "=" << 100000 - 100000 << " = " << bigint(100000) -bigint(100000) << ".\n";
    
    
    std::cout << "------minus-----.\n";
    std::cout
        << nsmallpos << " - " << nbigpos << "=" << -923 - -12345 << "  = " << nsmallpos -nbigpos << ".\n";

    std::cout << "------minus-----.\n";
    std::cout
        << 11 << " - " << -99 << "=" << 11 - -99 << "  = " << bigint(11) -bigint(-99) << ".\n";

    std::cout << "------minus-----.\n";
    std::cout
        << -11 << " - " << 99 << "=" << -11 - 99 << "  = " << bigint(-11) -bigint(99) << ".\n";

    std::cout << "------times-----.\n";
    std::cout
        << -111 << " * " << 99 << "=" << -111 * 99 << "  = " << bigint(-111) *bigint(99) << ".\n";
    
    std::cout << "------times-----.\n";
    std::cout
        << 1111 << " * " << 99 << "=" << 1111 * 99 << "  = " << bigint(1111) *bigint(99) << ".\n";
    
    std::cout << "------times-----.\n";
    std::cout
        << 1111 << " * " << 0 << "=" << 1111 * 0 << "  = " << bigint(1111) *bigint() << ".\n";
    return 0;
    
}
#include <vector>
#include <string>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
class bigint
{
private:
    // TODO: use reference?
    // TODO:
    /*
    Writing proper constructors which enforce the invariant,
        Making all data private and thus inaccessible to the user,
        Ensuring that any member function which changes the data does so in a way which preserves the invariant.
        */
    std::vector<uint8_t> digits;
    bool is_negative;

    uint8_t get_digit(const uint64_t n) const;

    bigint &set_digits(std::vector<uint8_t> n);
    bigint &push_back(const uint8_t n);
    bigint &pop_back();
    bigint &insert(std::vector<uint8_t>::iterator ind, const uint8_t num);
    bigint &erase(const std::vector<uint8_t>::iterator ind);
    size_t size() const;
    std::vector<uint8_t>::iterator begin();
    std::vector<uint8_t>::iterator end();

    bigint &set_negative(bool neg);

    // A default constructor, creating the integer 0.
    // A constructor that takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
    // A constructor that takes a string of digits and converts it to an arbitrary-precision integer.
    // Addition (+ and +=)
    // Subtraction (- and -=)
    // Multiplication (* and *=)
    // Negation (unary -)
    // Comparison (==, !=, <, >, <=, and >=)
    // Assignment (=)
    // Insertion (<<, to print the integer to a stream such as std::cout or a file)
public:
    // constructors done
    // TODO: change default; underscore
    bigint();
    bigint(int64_t n);
    bigint(std::string n);
    bigint(const bigint &other);
    ~bigint() = default;

    bool get_is_negative() const;
    std::vector<uint8_t> get_digits() const;
    bool is_zero() const;

    bigint operator+(bigint const &other) const;
    bigint &operator+=(bigint const &increment);
    bigint &operator++();
    bigint operator++(int);

    bigint operator-(bigint const &other) const;
    bigint &operator-=(bigint const &decrement);
    bigint &operator--();
    bigint operator--(int);

    bigint operator*(bigint const &other) const;
    bigint &operator*=(bigint const &multiplier);

    bigint operator-() const;
    bigint abs() const;

    bool operator==(bigint const &other) const;
    bool operator!=(bigint const &other) const;
    bool operator<(bigint const &other) const;
    bool operator>(bigint const &other) const;
    bool operator<=(bigint const &other) const;
    bool operator>=(bigint const &other) const;

    bigint &operator=(const bigint &other);

    friend std::ostream &operator<<(std::ostream &os, const bigint &n);
};

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
    if (n)
    {
        while (n)
        {
            push_back(static_cast<uint8_t>(n % 10));
            n /= 10;
        }
        std::reverse(begin(), end());
    }
    else
    {
        push_back(uint8_t(0));
    }
}
bigint::bigint(std::string n)
{
    if (n[0] == '-')
    {
        is_negative = true;
        n = n.substr(1);
    }
    else if (n[0] == '+')
    {
        is_negative = false;
        n = n.substr(1);
    }
    else
    {
        is_negative = false;
    }
    if (n.empty())
    {
        throw std::invalid_argument("bigint::bigint : Input string is empty.");
    }

    // n.erase(0, n.find_first_not_of('0'));
    if (n.empty())
    {
        n = "0";
    }

    for (char ch : n)
    {
        if (!std::isdigit(ch))
        {

            throw std::invalid_argument("bigint::bigint : Invalid character in input string: " + std::string(1, ch));
        }
        push_back(static_cast<uint8_t>(ch - '0'));
    }
}
bigint::bigint(const bigint &other) : digits(other.get_digits()), is_negative(other.get_is_negative()) {}
// helpers

uint8_t bigint::get_digit(const uint64_t n) const
{
    return n >= size() ? static_cast<uint8_t>(0) : get_digits()[n];
}

std::vector<uint8_t> bigint::get_digits() const
{
    return digits;
}

bigint &bigint::set_digits(std::vector<uint8_t> n)
{
    digits = n;
    return *this;
}

bigint &bigint::push_back(const uint8_t n)
{
    digits.push_back(n);
    return *this;
}

bigint &bigint::pop_back()
{
    digits.pop_back();
    return *this;
}

std::vector<uint8_t>::iterator bigint::begin()
{
    return digits.begin();
}

std::vector<uint8_t>::iterator bigint::end()
{
    return digits.end();
}

bigint &bigint::insert(std::vector<uint8_t>::iterator ind, const uint8_t num)
{
    digits.insert(ind, num);
    return *this;
}

bigint &bigint::erase(const std::vector<uint8_t>::iterator ind)
{
    digits.erase(ind);
    return *this;
}

size_t bigint::size() const
{
    return digits.size();
}

bool bigint::get_is_negative() const
{
    return is_negative;
}

bigint &bigint::set_negative(bool neg)
{
    is_negative = neg;
    return *this;
}

// overloaded operators
bigint bigint::operator+(bigint const &other) const
{
    bigint sum;

    if (get_is_negative() == other.get_is_negative())
    {
        uint8_t carry = static_cast<uint8_t>(0);
        size_t this_len = size();
        size_t other_len = other.size();
        size_t len = std::max(this_len, other_len);

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t sum_i = static_cast<uint8_t>(get_digit(this_len - 1 - i) + other.get_digit(other_len - 1 - i) + carry);
            carry = static_cast<uint8_t>(sum_i / 10);
            sum.insert(sum.begin(), static_cast<uint8_t>(sum_i % 10));
        }
        if (carry > 0)
            sum.insert(sum.begin(), static_cast<uint8_t>(carry));

        sum.set_negative(get_is_negative());
        sum.pop_back();
    }
    else if (get_is_negative())
    {
        sum = -(-*this - other);
    }
    else
        sum = *this - (-other);

    return sum;
}

bigint &bigint::operator+=(bigint const &increment)
{
    *this = *this + increment;
    return *this;
}

bigint &bigint::operator++()
{
    return *this += bigint(1);
}

bigint bigint::operator++(int)
{
    bigint temp = *this;
    ++(*this);
    return temp;
}

bigint bigint::operator-(bigint const &other) const
{
    bigint diff;

    if (get_is_negative() == other.get_is_negative())
    {
        diff.set_negative(*this >= other ? 0 : 1);

        bigint pos_num;
        bigint neg_num;

        if (abs() > other.abs())
        {
            pos_num = *this;
            neg_num = other;
        }
        else
        {
            pos_num = other;
            neg_num = *this;
        }

        size_t pos_len = pos_num.size();
        size_t neg_len = neg_num.size();
        size_t len = std::max(pos_len, neg_len);

        uint8_t borrow = static_cast<uint8_t>(0);

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t pos_i = pos_num.get_digit(pos_len - 1 - i);
            uint8_t neg_i = neg_num.get_digit(neg_len - 1 - i);
            uint8_t diff_i;

            if (pos_i < (neg_i + borrow))
            {
                diff_i = neg_i - pos_i + borrow;
                borrow = static_cast<uint8_t>(1);
                diff_i = static_cast<uint8_t>(10) - diff_i;
            }
            else
            {
                diff_i = pos_i - neg_i - borrow;
                borrow = static_cast<uint8_t>(0);
            }
            diff.insert(diff.begin(), diff_i);
        }

        diff.pop_back();
        uint64_t max_zero_iter = diff.size() - 1;
        for (uint64_t j = 0; j < max_zero_iter; j++)
        {
            if (diff.get_digit(0) == 0)
            {
                diff.erase(diff.begin());
            }
            else
                break;
        }
    }
    else if (get_is_negative())
    {
        diff = -(-*this + other);
    }
    else
        diff = *this + (-other);
    return diff;
}

bigint &bigint::operator-=(bigint const &decrement)
{
    *this = *this - decrement;
    return *this;
}

bigint &bigint::operator--()
{
    return *this -= bigint(1);
}

bigint bigint::operator--(int)
{
    bigint temp = *this;
    --(*this);
    return temp;
}

bigint bigint::operator*(bigint const &other) const
{
    bigint prod;

    if (is_zero() || other.is_zero())
        return prod;

    uint8_t carry = static_cast<uint8_t>(0);
    size_t inner_iter = size();
    size_t outer_iter = other.size();

    for (uint64_t i = 0; i < outer_iter; i++)
    {
        bigint digits_i;
        for (uint64_t j = 0; j < inner_iter; j++)
        {
            uint8_t prod_i = static_cast<uint8_t>(other.get_digit(outer_iter - 1 - i) * get_digit(inner_iter - 1 - j) + carry);
            carry = static_cast<uint8_t>(prod_i / 10);
            uint8_t digits_i_j = static_cast<uint8_t>(prod_i % 10);

            digits_i.insert(digits_i.begin(), digits_i_j);
        }
        for (uint64_t k = 0; k < i; k++)
        {
            digits_i.push_back(uint8_t(0));
        }

        if (carry > 0)
        {
            digits_i.insert(digits_i.begin(), static_cast<uint8_t>(carry));
            carry = static_cast<uint8_t>(0);
        }

        digits_i.pop_back();
        bigint prodArch = prod;
        prod += digits_i;
    }

    prod.set_negative(!(get_is_negative() == other.get_is_negative()));
    return prod;
}

bigint &bigint::operator*=(bigint const &multiplier)
{
    *this = *this * multiplier;
    return *this;
}

bigint bigint::operator-() const
{
    bigint flip = *this;
    flip.set_negative(!get_is_negative());

    return flip;
}

bigint bigint::abs() const
{
    bigint abs = *this;
    abs.set_negative(0);

    return abs;
}

bool bigint::operator==(bigint const &other) const
{

    if (get_is_negative() == other.get_is_negative() && get_digits() == other.get_digits())
        return true;
    else
    {
        if (is_zero() && other.is_zero())
            return true;
        else
            return false;
    }
}

bool bigint::is_zero() const
{
    return std::all_of(get_digits().begin(), get_digits().end(), [](uint8_t digit)
                       { return digit == 0; });
}

bool bigint::operator!=(bigint const &other) const
{
    if (get_is_negative() != other.get_is_negative() || get_digits() != other.get_digits())
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
    set_digits(other.get_digits());
    return *this;
}

std::ostream &operator<<(std::ostream &os, const bigint &n)
{
    if (n.get_is_negative())
    {
        os << '-';
    }
    for (uint8_t digit : n.get_digits())
    {
        os << static_cast<uint16_t>(digit);
    }
    return os;
}
/**
 * @file bigint.hpp
 * @author Chenwei Song
 * @brief A class to represent arbitrary-precision integers.
 * @version 0.1
 * @date 2024-12-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <string>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
class bigint
{
private:
    /**
     * @brief
     *
     */
    std::vector<uint8_t> digits; ///< Digits of the number stored in reverse order (least significant digit first).
    bool is_negative;            ///< Sign of the number (true for negative, false for non-negative).

    /**
     * @brief Gets a digit at a specific index.
     *
     * @param n Index of the digit.
     * @return The digit at the specified index or 0 if out of bounds.
     */
    uint8_t get_digit(const uint64_t n) const;

    /**
     * @brief Set the digits object
     *
     * @param n Vector of digits.
     * @return Reference to the updated bigint.
     */
    bigint &set_digits(std::vector<uint8_t> n);
    /**
     * @brief Adds a digit to the end of the bigint.
     *
     * @param n Digit to add.
     * @return Reference to the updated bigint.
     */
    bigint &push_back(const uint8_t n);
    /**
     * @brief Removes the last digit of the bigint.
     *
     * @return Reference to the updated bigint.
     */
    bigint &pop_back();
    /**
     * @brief Inserts a digit at the specified position.
     *
     * @param ind Iterator to the position.
     * @param num Digit to insert.
     * @return Reference to the updated bigint.
     */
    bigint &insert(std::vector<uint8_t>::iterator ind, const uint8_t num);
    /**
     * @brief Erases a digit at the specified position.
     *
     * @param ind Iterator to the position.
     * @return Reference to the updated bigint.
     */
    bigint &erase(const std::vector<uint8_t>::iterator ind);

    /**
     * @brief Set the is_negative object
     *
     * @param neg True if the bigint is negative.
     * @return Reference to the updated bigint.
     */
    bigint &set_negative(bool neg);

    /**
     * @brief Returns an iterator to the beginning of the digits.
     *
     * @return Iterator pointing to the first digit.
     */
    std::vector<uint8_t>::iterator begin();
    /**
     * @brief Returns an iterator to the end of the digits.
     *
     * @return Iterator pointing to one past the last digit.
     */
    std::vector<uint8_t>::iterator end();

    /**
     * @brief Returns the number of digits in the bigint.
     *
     * @return The number of digits.
     */
    size_t size() const;
    /**
     * @brief Checks whether the bigint is zero.
     *
     * @return True if the bigint represents the value 0, false otherwise.
     */
    bool is_zero() const;

public:
    /**
     * @brief Default constructor. Initializes the bigint to 0.
     *
     */
    bigint();
    /**
     * @brief Constructor from a signed 64-bit integer.
     *
     * @param n The integer to initialize with.
     */
    bigint(int64_t n);
    /**
     * @brief Constructor from a string of digits.
     *
     * @param n The string representation of the number.
     * @throws std::invalid_argument if the string is contains non-number characters.
     */
    bigint(std::string n);
    /**
     * @brief Copy constructor.
     *
     * @param other The bigint to copy.
     */
    bigint(const bigint &other);
    /**
     * @brief Destroy the bigint object
     *
     */
    ~bigint() = default;

    /**
     * @brief Get the is_negative object
     *
     * @return True if the bigint is negative, false otherwise.
     */
    bool get_is_negative() const;
    /**
     * @brief Get the digits object
     *
     * @return A vector containing the digits of the bigint.
     */
    std::vector<uint8_t> get_digits() const;

    /**
     * @brief Adds two bigints.
     *
     * @param other The other bigint to add.
     * @return The sum of the two bigints.
     */
    bigint operator+(bigint const &other) const;
    /**
     * @brief Adds another bigint to this bigint.
     *
     * @param increment The bigint to add.
     * @return Reference to the updated bigint.
     */
    bigint &operator+=(bigint const &increment);
    /**
     * @brief Pre-increment operator.
     *
     * @return Reference to the updated bigint.
     */
    bigint &operator++();
    /**
     * @brief Post-increment operator.
     *
     * @return The value of the bigint before incrementing.
     */
    bigint operator++(int);

    /**
     * @brief Subtracts one bigint from another.
     *
     * @param other The bigint to subtract.
     * @return The difference of the two bigints.
     */
    bigint operator-(bigint const &other) const;
    /**
     * @brief Subtracts another bigint from this bigint.
     *
     * @param decrement The bigint to subtract.
     * @return Reference to the updated bigint.
     */
    bigint &operator-=(bigint const &decrement);
    /**
     * @brief Pre-decrement operator.
     *
     * @return Reference to the updated bigint.
     */
    bigint &operator--();
    /**
     * @brief Post-decrement operator.
     *
     * @return The value of the bigint before decrementing.
     */
    bigint operator--(int);

    /**
     * @brief Multiplies two bigints.
     *
     * @param other other The bigint to multiply.
     * @return The product of the two bigints.
     */
    bigint operator*(bigint const &other) const;
    /**
     * @brief Multiplies another bigint with this bigint.
     *
     * @param multiplier The bigint to multiply.
     * @return Reference to the updated bigint.
     */
    bigint &operator*=(bigint const &multiplier);

    /**
     * @brief Flips the sign of the bigint.
     *
     * @return A new bigint that is the negation of the current bigint.
     */
    bigint operator-() const;
    /**
     * @brief The absolute value of a bigint
     *
     * @return A new bigint that is the absolute value of the current bigint.
     */
    bigint abs() const;

    /**
     * @brief Compares two bigints for equality.
     *
     * @param other The bigint to compare.
     * @return True if the two bigints are equal, false otherwise.
     */
    bool operator==(bigint const &other) const;
    /**
     * @brief Compares two bigints for inequality.
     *
     * @param other The bigint to compare.
     * @return True if the two bigints are not equal, false otherwise.
     */
    bool operator!=(bigint const &other) const;
    /**
     * @brief Compares if this bigint is less than another bigint.
     *
     * @param other The bigint to compare.
     * @return True if this bigint is less than the other, false otherwise.
     */
    bool operator<(bigint const &other) const;
    /**
     * @brief Compares if this bigint is greater than another bigint.
     *
     * @param other The bigint to compare.
     * @return True if this bigint is greater than the other, false otherwise.
     */
    bool operator>(bigint const &other) const;
    /**
     * @brief Compares if this bigint is less than or equal to another bigint.
     *
     * @param other The bigint to compare.
     * @return True if this bigint is less than or equal to the other, false otherwise.
     */
    bool operator<=(bigint const &other) const;
    /**
     * @brief Compares if this bigint is greater than or equal to another bigint.
     *
     * @param other The bigint to compare.
     * @return True if this bigint is greater than or equal to the other, false otherwise.
     */
    bool operator>=(bigint const &other) const;

    /**
     * @brief Assigns one bigint to another.
     *
     * @param other The bigint to assign from.
     * @return Reference to the updated bigint.
     */
    bigint &operator=(const bigint &other);

    /**
     * @brief Outputs the bigint to a stream.
     *
     * @param os The output stream.
     * @param n The bigint to print.
     * @return Reference to the output stream.
     */
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

    n.erase(0, n.find_first_not_of('0'));
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
    return n >= size() ? 0 : get_digits()[n];
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
    if (is_zero())
        return 0;
    size_t length = get_digits().size();
    std::size_t startIndex = 0;

    while (startIndex < length && get_digits()[startIndex] == 0)
    {
        ++startIndex;
    }
    return length - startIndex;
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
        uint8_t carry = 0;
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
            sum.insert(sum.begin(), carry);

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

        uint8_t borrow = 0;

        for (uint64_t i = 0; i < len; i++)
        {
            uint8_t pos_i = pos_num.get_digit(pos_len - 1 - i);
            uint8_t neg_i = neg_num.get_digit(neg_len - 1 - i);
            uint8_t diff_i;

            if (pos_i < (neg_i + borrow))
            {
                diff_i = static_cast<uint8_t>(neg_i - pos_i + borrow);
                borrow = 1;
                diff_i = static_cast<uint8_t>(10 - diff_i);
            }
            else
            {
                diff_i = static_cast<uint8_t>(pos_i - neg_i - borrow);
                borrow = 0;
            }
            diff.insert(diff.begin(), diff_i);
        }

        diff.pop_back();
        uint64_t max_zero_iter = diff.get_digits().size() - 1;
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

    uint8_t carry = 0;
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
            digits_i.insert(digits_i.begin(), carry);
            carry = 0;
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
        {
            return false;
        }
    }
}

bool bigint::is_zero() const
{
    for (const uint8_t &digit : get_digits())
    {
        if (digit != 0)
        {
            return false;
        }
    }
    return true;
}

bool bigint::operator!=(bigint const &other) const
{
    return !(*this == other);
}

bool bigint::operator<(bigint const &other) const
{
    if (*this == other)
        return false;
    else if (get_is_negative() != other.get_is_negative())
        return get_is_negative();
    else if (size() > other.size())
    {
        return get_is_negative();
    }
    else if (size() == other.size())
    {
        for (uint64_t i = 0; i < size(); i++)
        {
            if (get_digit(i) != other.get_digit(i))
                return get_digit(i) > other.get_digit(i) ? get_is_negative() : !get_is_negative();
        }
        return false;
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
#include <vector>
#include <string>
#include <inttypes.h>
#include <iostream>
class bigint
{
    std::vector<int8_t> digits;
    bool is_negative;
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
    bigint();
    bigint(int64_t n);
    bigint(std::string n);
    bigint(const bigint &other);
    ~bigint() = default;

    bigint operator+(bigint const &other) const;
    bigint operator+=(bigint const &increment) const;

    bigint operator-(bigint const &other);
    bigint operator-=(bigint const &decrement) const;

    bigint operator*(bigint const &other) const;
    bigint operator*=(bigint const &multiplier) const;

    bigint operator-() const; //

    bool operator==(bigint const &other) const; //
    bool operator!=(bigint const &other) const; //
    bool operator<(bigint const &other) const;  //
    bool operator>(bigint const &other) const;  //
    bool operator<=(bigint const &other) const;
    bool operator>=(bigint const &other) const;

    bigint &operator=(const bigint &other); //

    friend std::ostream &operator<<(std::ostream &os, const bigint &n); //
};
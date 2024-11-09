#include <vector>
#include <string>
#include <inttypes.h>
#include <iostream>
class bigint
{
private:
    std::vector<uint8_t> digits;
    bool is_negative;

    uint8_t get_digit(const uint64_t n) const;//
    std::vector<uint8_t> get_digits() const;//

    bigint& set_digits(std::vector<uint8_t> n);
    bigint& push_back(const uint8_t n);//
    bigint& pop_back();//
    bigint& insert(std::vector<uint8_t>::iterator ind,const uint8_t num);//
    bigint& erase(const std::vector<uint8_t>::iterator ind);//
    size_t size() const;//
    std::vector<uint8_t>::iterator begin();//
    std::vector<uint8_t>::iterator end();//

    bool get_is_negative() const;//
    bigint& set_negative(bool neg);//
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

    bigint operator+(bigint const &other) const;//
    bigint& operator+=(bigint const &increment);//

    bigint operator-(bigint const &other) const;//
    bigint& operator-=(bigint const &decrement);//

    bigint operator*(bigint const &other) const;//
    bigint& operator*=(bigint const &multiplier);//

    bigint operator-() const; //
    bigint abs() const; //

    bool operator==(bigint const &other) const; //
    bool operator!=(bigint const &other) const; //
    bool operator<(bigint const &other) const;  //
    bool operator>(bigint const &other) const;  //
    bool operator<=(bigint const &other) const; //
    bool operator>=(bigint const &other) const; //

    bigint& operator=(const bigint &other); //

    friend std::ostream& operator<<(std::ostream &os, const bigint &n); //
};
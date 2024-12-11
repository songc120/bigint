/**
 * @file test.cpp
 * @author Chenwei Song
 * @brief Unit tests for the `bigint` class, covering constructors, arithmetic operations, comparisons, and edge cases.
 * @version 0.1
 * @date 2024-12-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "bigint.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <random>

/**
 * @brief Converts a string of digits to a vector of `uint8_t`.
 * 
 * @param n The string to convert.
 * @return A vector of digits (`uint8_t`), ignoring non-digit characters.
 */
std::vector<uint8_t> stringToDigits(const std::string &n)
{
    std::vector<uint8_t> result;
    for (char ch : n)
    {
        if (std::isdigit(ch))
        {
            result.push_back(static_cast<uint8_t>(ch - '0'));
        }
    }
    return result;
}
/**
 * @brief Unit tests for the constructors of the `bigint` class.
 * 
 */
void unit_test_constructor()
{
    std::ofstream logFile("./unit_test_constructor.log");
    std::cout.rdbuf(logFile.rdbuf());
    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
        EXIT_FAILURE;
    }
    // Unit tests for default constructor
    bigint default_zero = bigint();
    bigint int_zero = bigint(0);
    bigint str_zero = bigint("0");
    std::cout << "Comparing default constructor with int_zero: " << default_zero << " = " << int_zero << '\n';
    assert(default_zero == int_zero && "Default constructor test failed!");
    std::cout << "Comparing default constructor with str_zero: " << default_zero << " = " << str_zero << '\n';
    assert(default_zero == str_zero && "Default constructor test failed!");

    std::cout << "Unit tests for default constructor passed: 2 " << '\n';
    std::cout << "------------------------------------------------" << std::endl;

    // Unit test asserting bigint(int64_t) == bigint(string)
    uint64_t total_tests_64 = 10;
    uint64_t passed_tests_64 = 0;
    std::random_device rd;
    std::mt19937_64 mt64(rd());
    std::uniform_int_distribution<int64_t> dist(0, std::numeric_limits<int64_t>::max());
    std::uniform_int_distribution<int> signDist(0, 1);

    for (uint64_t i = 0; i < total_tests_64; i++)
    {
        int64_t randomInt = dist(mt64);
        if (signDist(mt64))
        {
            randomInt = -randomInt;
        }
        std::string randomStr = std::to_string(randomInt);
        bigint fromInt(randomInt);
        bigint fromString(randomStr);
        std::cout << "Testing constructor using " << randomInt << '\n';
        assert(fromString == fromInt && "Constructor from string/int test failed!");
        passed_tests_64++;
    }

    std::cout << "Unit tests for constructors from string/int passed: " << passed_tests_64 << '\n';
    std::cout << "------------------------------------------------" << std::endl;

    // Unit test for bigint(vary large number)
    uint64_t total_tests_big = 10;
    uint64_t passed_tests_big = 0;

    for (uint64_t i = 0; i < total_tests_big; i++)
    {
        std::string largeNumber;
        bool big_sign = true;
        for (uint64_t j = 0; j < 3; j++)
        {
            largeNumber += std::to_string(dist(mt64));
        }
        if (signDist(mt64))
        {

            big_sign = false;
            largeNumber = "-" + largeNumber;
        }
        bigint very_big(largeNumber);
        std::cout << "Testing constructor using " << largeNumber << '\n';
        assert(!big_sign == very_big.get_is_negative() && "Constructor from very large number failed in sign!");
        assert(very_big.get_digits() == stringToDigits(largeNumber) && "Constructor from very large number failed in digits!");
        assert(very_big == bigint(very_big) && "Copy constructor from very large number failed in sign!");
        passed_tests_big++;
    }

    std::cout << "Unit tests for constructors from very large number: " << passed_tests_big << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    logFile.close();
}
/**
 * @brief Unit tests for arithmetic operations and comparisons.
 * 
 * @return Exit code (0 for success, non-zero for failure).
 */
int8_t unit_test_2()
{
    std::ofstream logFile("./unit_test_2.log");
    std::cout.rdbuf(logFile.rdbuf());
    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
        EXIT_FAILURE;
    }
    std::string filename = "./data/unit_test_2data.txt";
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cerr << "Error: Failed to open input file 'filename.txt'. Please check if the file exists and you have the necessary permissions." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    u_int64_t total_tests = 0;

    while (std::getline(input, line))
    {

        ++total_tests;
        std::istringstream string_stream(line);
        std::string left, op, right, eq, result;
        string_stream >> left >> op >> right >> eq >> result;
        std::cout << "Testing operation " << op << ": " << left << op << right << "=" << result << '\n';
        bigint bigint1(left);
        bigint bigint2(right);

        if (op == "+" || op == "-" || op == "*" || op == "+=" || op == "-=" || op == "*=")
        {

            bigint expected_result(result);

            if (op == "+")
            {
                assert(bigint1 + bigint2 == expected_result && "Addition test a + b = c failed!");
                assert(bigint2 + bigint1 == expected_result && "Addition test b + a = c failed!");

                assert(bigint1 + bigint2 + expected_result == expected_result + bigint1 + bigint2 && "Addition test a + b + c = c + a + b failed!");
                assert(bigint1 - bigint2 + expected_result == expected_result + bigint1 - bigint2 && "Addition/Subtraction test a - b + c = c + a - b failed!");
                assert(bigint1 - bigint2 + expected_result == expected_result - bigint2 + bigint1 && "Addition/Subtraction test a - b + c = c - b + a failed!");
                assert(bigint1 - bigint2 + expected_result == -bigint2 + bigint1 + expected_result && "Addition/Subtraction test a - b + c = - b + a + c failed!");

                assert((bigint1 + (bigint2 + expected_result)) == ((bigint1 + bigint2) + expected_result) && "Associativity test a + (b + c) = (a + b) + c failed!");

                bigint zero("0");
                assert((bigint1 + zero) == bigint1 && "Addition identity test a + 0 = a failed!");
                assert((zero + bigint1) == bigint1 && "Addition identity test 0 + a = a failed!");

                assert((bigint1 + (-bigint1)) == zero && "Addition inverse test a + (-a) = 0 failed!");
            }
            else if (op == "-")
            {
                bigint zero("0");
                assert((bigint1 - bigint1) == zero && "Self-inverse test a - a = 0 failed!");

                assert((bigint1 - bigint2 + bigint2) == bigint1 && "Inverse test a - b + b = a failed!");
                assert((bigint1 + bigint2 - bigint2) == bigint1 && "Inverse test a + b - b = a failed!");

                assert(bigint1 - bigint2 == expected_result && "Subtraction test a - b = c failed!");
                assert(bigint1 == bigint2 + expected_result && "Subtraction test a = b + c failed!");
                assert(bigint2 == bigint1 - expected_result && "Subtraction test b = a - c failed!");
            }
            else if (op == "*")
            {
                assert(bigint1 * bigint2 == expected_result && "Multiplication test a * b = c failed!");
                assert(bigint2 * bigint1 == expected_result && "Multiplication test b * a = c failed!");
                assert((bigint1 * (bigint2 * expected_result)) == ((bigint1 * bigint2) * expected_result) && "Associativity test a * (b * c) = (a * b) * c failed!");

                bigint one("1");
                assert((bigint1 * one) == bigint1 && "Multiplication identity test a * 1 = a failed!");
                assert((one * bigint1) == bigint1 && "Multiplication identity test 1 * a = a failed!");
                bigint zero("0");

                assert((bigint1 * zero) == zero && "Multiplication by zero test a * 0 = 0 failed!");
                assert((zero * bigint1) == zero && "Multiplication by zero test 0 * a = 0 failed!");
            }

            if (op == "+=")
            {
                bigint1 += bigint2;
                assert(bigint1 == expected_result && "Addition-assignment test failed!");
            }
            else if (op == "-=")
            {
                bigint1 -= bigint2;
                assert(bigint1 == expected_result && "Subtraction-assignment test failed!");
            }
            else if (op == "*=")
            {
                bigint1 *= bigint2;
                assert(bigint1 == expected_result && "Multiplication-assignment test failed!");
            }
        }
        else
        {
            bool expected_result = (result == "True");
            if (op == "==")
            {
                assert(bigint1 == bigint2 == expected_result && "Equality test failed!");
                assert(bigint2 == bigint1 == expected_result && "Equality test failed!");
            }
            else if (op == "!=")
            {
                assert(bigint1 != bigint2 == expected_result && "Inequality test failed!");
                assert(bigint2 != bigint1 == expected_result && "Inequality test failed!");
            }
            else if (op == ">")
            {
                assert(bigint1 > bigint2 == expected_result && "Comparison > test failed!");
                assert(-bigint1 < -bigint2 == expected_result && "Comparison > test failed!");
            }
            else if (op == ">=")
            {
                assert(bigint1 >= bigint2 == expected_result && "Comparison >= test failed!");
                assert(-bigint1 <= -bigint2 == expected_result && "Comparison >= test failed!");
            }
            else if (op == "<")
            {
                assert(bigint1 < bigint2 == expected_result && "Comparison < test failed!");
                assert(-bigint1 > -bigint2 == expected_result && "Comparison < test failed!");
            }
            else if (op == "<=")
            {
                assert(bigint1 <= bigint2 == expected_result && "Comparison <= test failed!");
                assert(-bigint1 >= -bigint2 == expected_result && "Comparison <= test failed!");
            }
        }
    }

    input.close();
    std::cout << "Unit tests with 2 args passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    logFile.close();
    return EXIT_SUCCESS;
}
/**
 * @brief Unit tests for unary operations, such as negation and increment/decrement.
 * 
 * @return Exit code (0 for success, non-zero for failure). 
 */
int8_t unit_test_1()
{
    std::ofstream logFile("./unit_test_1.log");
    std::cout.rdbuf(logFile.rdbuf());
    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
        EXIT_FAILURE;
    }
    

    std::string filename = "./data/unit_test_1data.txt";
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cerr << "Error: Failed to open input file 'filename.txt'. Please check if the file exists and you have the necessary permissions." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    u_int64_t total_tests = 0;

    while (std::getline(input, line))
    {

        ++total_tests;
        std::istringstream string_stream(line);
        std::string left, right, eq, result;
        string_stream >> left >> right >> eq >> result;

        bigint expected_result(result);

        if (right == "++")
        {
            std::string op = right;
            bigint old_value = bigint(left);
            std::cout << "Testing operation post increment" << ": " << left << op << " = " << result << '\n';
            old_value++;
            assert(old_value == expected_result && "Post-increment test failed!");
        }
        else if (right == "--")
        {
            std::string op = right;
            bigint old_value = bigint(left);
            std::cout << "Testing operation post decrement" << ": " << left << op << " = " << result << '\n';
            old_value--;
            assert(old_value == expected_result && "Post-decrement test failed!");
        }
        else if (left == "++")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation pre increment" << ": " << old_value << op << " = " << result << '\n';
            ++old_value;
            assert(old_value == expected_result && "Pre-increment test failed!");
        }
        else if (left == "--")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation pre decrement" << ": " << old_value << op << " = " << result << '\n';
            --old_value;
            assert(old_value == expected_result && "Pre-decrement test failed!");
        }
        else if (left == "-")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation " << op << ": " << op << old_value << " = " << result << '\n';
            assert(-old_value == expected_result && "Unary negation test failed!");
            assert(old_value == -expected_result && "Unary negation test failed!");
        }
    }

    input.close();
    std::cout << "Unit tests with 1 args passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    
    logFile.close();
    return EXIT_SUCCESS;
}
/**
 * @brief Unit tests for edge cases in `bigint` operations.
 * 
 */
void edge_test(){
    std::ofstream logFile("./unit_test_edge.log");
    std::cout.rdbuf(logFile.rdbuf());
    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open log file!" << std::endl;
        EXIT_FAILURE;
    }

    u_int64_t total_tests = 11;

    bigint zero = bigint(0);
    bigint one = bigint(1);
    bigint n_one = bigint(-1);

    std::cout << "Testing zero == zero" << '\n';
    assert(zero == zero && "Comparison == failed!");
    std::cout << "Testing zero == -zero" << '\n';
    assert(zero == -zero && "Comparison == test failed!");
    std::cout << "Testing !(zero != zero)" << '\n';
    assert(!(zero != zero) && "Comparison != test failed!");
    std::cout << "Testing !(zero != -zero)" << '\n';
    assert(!(zero != -zero) && "Comparison != test failed!");
    std::cout << "Testing !(zero > -zero)" << '\n';
    assert(!(zero > -zero) && "Comparison > test failed!");
    std::cout << "Testing (zero >= -zero)" << '\n';
    assert((zero >= -zero) && "Comparison >= test failed!");
    std::cout << "Testing !(-zero < zero)" << '\n';
    assert(!(-zero < zero) && "Comparison < test failed!");
    std::cout << "Testing (zero <= zero)" << '\n';
    assert((zero <= zero) && "Comparison <= test failed!");

    std::cout << "Testing (zero + one == one)" << '\n';
    assert((zero + one == one) && "Addition test failed!");
    std::cout << "Testing (one + n_one == zero)" << '\n';
    assert((one + n_one == zero) && "Addition test failed!");
    std::cout << "(zero - one == n_one)" << '\n';
    assert((zero - one == n_one) && "Subtraction test failed!");

    std::cout << "Edge tests passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;

    logFile.close();
}
/**
 * @brief Main entry point for running all unit tests.
 * 
 * @return Exit code (0 for success, non-zero for failure).
 */
int main()
{
    try
    {
        std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    
        unit_test_2();
        unit_test_1();
        unit_test_constructor();
        edge_test();

        std::cout.rdbuf(originalCoutBuffer);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }
    return 0;
}
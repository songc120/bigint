#include "bigint.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <random>

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
uint64_t unit_test_constructor()
{
    // Unit tests for default constructor
    uint64_t default_tests = 2;
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
        passed_tests_big++;
    }

    std::cout << "Unit tests for constructors from very large number: " << passed_tests_big << '\n';
    std::cout << "------------------------------------------------" << std::endl;

    return default_tests + passed_tests_64 + passed_tests_big;
}

int8_t unit_test_2()
{
    std::string filename = "./data/unit_test_2data.txt";
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cout << "Error opening input file!";
        return -1;
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
                assert(expected_result -  bigint1 == bigint2 && "Addition test c - a = b failed!");
                assert(expected_result -  bigint2 == bigint1 && "Addition test c - b = a failed!");
            }
            else if (op == "-")
            {
                assert(bigint1 - bigint2 == expected_result && "Subtraction test failed!");
            }
            else if (op == "*")
            {
                assert(bigint1 * bigint2 == expected_result && "Multiplication test failed!");
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
            }
            else if (op == "!=")
            {
                assert(bigint1 != bigint2 == expected_result && "Inequality test failed!");
            }
            else if (op == ">")
            {
                assert(bigint1 > bigint2 == expected_result && "Comparison > test failed!");
            }
            else if (op == ">=")
            {
                assert(bigint1 >= bigint2 == expected_result && "Comparison >= test failed!");
            }
            else if (op == "<")
            {
                assert(bigint1 < bigint2 == expected_result && "Comparison < test failed!");
            }
            else if (op == "<=")
            {
                assert(bigint1 <= bigint2 == expected_result && "Comparison <= test failed!");
            }
        }
    }

    input.close();
    std::cout << "Unit tests with 2 args passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    return 0;
}

int8_t unit_test_1()
{
    std::string filename = "./data/unit_test_1data.txt";
    std::ifstream input(filename);

    if (!input.is_open())
    {
        std::cout << "Error opening input file!";
        return -1;
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
            std::cout << "Testing operation " << op << ": "  << op << old_value << " = " << result << '\n';
            assert(-old_value == expected_result && "Unary negation test failed!");
        }
    }

    input.close();
    std::cout << "Unit tests with 1 args passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    return 0;
}

int main()
{
    try
    {
        // unit_test_2();
        unit_test_1();
        // unit_test_constructor();
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    /*
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
        << -222 << " * " << 99 << "=" << -222 * 99 << "  = " << bigint(-222) *bigint(99) << ".\n";

    std::cout << "------times-----.\n";
    std::cout
        << 1111 << " * " << 9999 << "=" << 1111 * 9999 << "  = " << bigint(1111) *bigint(9999) << ".\n";

    std::cout << "------times-----.\n";
    std::cout
        << 1111 << " * " << 99 << "=" << 1111 * 99 << "  = " << bigint(1111) *bigint(99) << ".\n";
    bigint m1=bigint(1111);
    m1*= bigint(99);
    std::cout
        << m1<< ".\n";

    std::cout << "------times-----.\n";
    std::cout
        << 99 << " * " << 23456 << "=" << 99 * 23456 << "  = " << bigint(99) *bigint(23456) << ".\n";

    std::cout << "------times-----.\n";
    std::cout
        << 1111 << " * " << 0 << "=" << 1111 * 0 << "  = " << bigint(1111) *bigint() << ".\n";
    m1*= bigint();
    std::cout
        << m1<< ".\n";
        */
    return 0;
}
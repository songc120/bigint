#include "bigint.hpp"
#include <fstream>
#include <sstream>
#include <cassert>

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
        std::cout << "Testing operation" << op << ": " << left << op << right << "=" << result << '\n';

        if (op == "+" || op == "-" || op == "*")
        {
            bigint bigint1(left);
            bigint bigint2(right);
            bigint expected_result(result);

            if (op == "+")
            {
                assert(bigint1 + bigint2 == expected_result && "Addition test failed!");
            }
            else if (op == "-")
            {
                assert(bigint1 - bigint2 == expected_result && "Subtraction test failed!");
            }
            else if (op == "*")
            {
                assert(bigint1 * bigint2 == expected_result && "Multiplication test failed!");
            }
        }
        else if (op == "+=" || op == "-=" || op == "*=")
        {
            bigint bigint1(left);
            bigint bigint2(right);
            bigint expected_result(result);

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
    }

    input.close();
    std::cout << "Unit tests passed: " << total_tests << '\n';
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
            std::cout << "Testing operation post" << op << ": " << left << op << "=" << result << '\n';
            old_value++;
            assert(old_value == expected_result && "Post-increment test failed!");
        }
        else if (right == "--")
        {
            std::string op = right;
            bigint old_value = bigint(left);
            std::cout << "Testing operation post" << op << ": " << left << op << "=" << result << '\n';
            old_value--;
            assert(old_value == expected_result && "Post-decrement test failed!");
        }
        else if (left == "++")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation pre" << op << ": " << left << op << "=" << result << '\n';
            ++old_value;
            assert(old_value == expected_result && "Pre-increment test failed!");
        }
        else if (left == "--")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation pre" << op << ": " << left << op << "=" << result << '\n';
            --old_value;
            assert(old_value == expected_result && "Pre-decrement test failed!");
        }
        else if (left == "-")
        {
            std::string op = left;
            bigint old_value = bigint(right);
            std::cout << "Testing operation " << op << ": " << left << op << "=" << result << '\n';
            assert(-old_value == expected_result && "Unary negation test failed!");
        }
    }

    input.close();
    std::cout << "Unit tests passed: " << total_tests << '\n';
    std::cout << "------------------------------------------------" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    try
    {
        // unit_test_2();
        unit_test_1();
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
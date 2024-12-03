#include "bigint.hpp"
#include <fstream>
#include <sstream>
#include <cassert>

int main(int argc, char *argv[])
{
    try
    {

        // if (argc < 2)
        // {
        //     std::cout << "Usage examples:\n";
        //     std::cout << " ./test 123\n";
        //     return 1;
        // }
        // else
        // {
        //     bigint given = bigint(argv[1]);

        //     std::cout
        //         << "Bigint from input:" << given << "\n";
        //     std::cout << "++bigint:" << ++given << "\n";
        //     std::cout
        //         << "Bigint from input now:" << given << "\n";
        //     std::cout << "bigint++:" << given++ << "\n";
        //     std::cout
        //         << "Bigint from input now:" << given << "\n";
        //     std::cout << "--bigint:" << --given << "\n";
        //     std::cout
        //         << "Bigint from input now:" << given << "\n";
        //     std::cout << "bigint--:" << given-- << "\n";
        //     std::cout
        //         << "Bigint from input now:" << given << "\n";
        //     std::cout
        //         << "0-1:" << bigint(0) - bigint(1) << "\n";
        // }
        std::string filename = "./data/results2params.txt";
        std::ifstream input(filename);

        if (!input.is_open())
        {
            std::cout << "Error opening input file!";
            return -1;
        }

        std::string line;
        u_int64_t total_tests = 0;
        u_int64_t passed_tests = 0;

        while (std::getline(input, line))
        {

            ++total_tests;
            std::istringstream string_stream(line);
            std::string int1, int2, op, res;

            string_stream >> int1 >> int2 >> op >> res;
            bigint bigint1(int1);
            bigint bigint2(int2);
            bigint expected_result(res);

            std::cout << "Tesing operation" << op << ": " << int1 << op << int2 << "=" << res << '\n';
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
            ++passed_tests;
        }

        input.close();
        std::cout << "Tests passed: " << passed_tests << "/" << total_tests << std::endl;
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
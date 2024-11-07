#include <iostream>
#include <vector>

int8_t add_one(const int8_t n)
{
    return n + 1;
}

int8_t get_digit(std::vector<int> v, const int8_t n)
{
    size_t len = v.size();
    return n > len - 1 ? 0 : v[n];
}

int main()
{
    std::vector<int> v1 = {1, 1, 1, 1, 1, 2, 3, 4, 5, 6};
    std::vector<int> v2 = {9, 2, 3, 4, 5, 6};
    std::vector<int> v3;

    int carry = 0;

    size_t this_len = v1.size();
    size_t other_len = v2.size();
    size_t len = std::max(this_len, other_len);

    for (int i = 0; i < len; i++)
    {
        int sum_i = get_digit(v1, this_len - 1 - i) + get_digit(v2, other_len - 1 - i) + carry;
        carry = sum_i / 10;
        v3.insert(v3.begin(), sum_i % 10);
    }
    if (carry)
        v3.insert(v3.begin(), carry);

    // Print out the vector
    for (int n : v3)
        std::cout
            << n << ' ';

    std::cout << '\n';
    std::cout << v1[0] << '\n';
    std::cout << v1[6] << '\n';
    std::cout << v1[7] << '\n';
    std::cout << v1[70] << '\n';

    std::cout << 1111123456 + 923456 << '\n';
}

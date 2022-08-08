// Palindrome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <future>

unsigned long long int modnum(int num, unsigned long long search_begin, unsigned long long search_end);

int main()
{
    const auto thread_count = std::thread::hardware_concurrency();
    std::cout << "\nFind the largest palindrome made from the product of two numbers. Enter the max amount of digits for the numbers:\n";

    int result = 0;
    scanf_s("%d", &result);

    unsigned long long int max_val = pow(10, result);
    unsigned long long int start = pow(10, result - 1);
    unsigned long long int delta = max_val - start;
    unsigned long long int diff = delta / thread_count;
    std::vector<std::future<unsigned long long int>> results;
    for (int i = 0; i < thread_count; i++)
    {
        results.emplace_back(std::async(std::launch::async, modnum, result, start, start + diff));
        start += diff;


    }
    std::vector<unsigned long long int> ints_results;
    for (auto& t : results)
    {
        auto wait_for_int = t.get();
        ints_results.push_back(wait_for_int);

    }
    std::sort(ints_results.begin(), ints_results.end());

    std::cout << "The largest pallindrome made from " << result << " digits" << "\nEnded up being " << ints_results[(ints_results.size() - 1)];
    return 0;
}

unsigned long long int modnum(int digits, unsigned long long search_begin, unsigned long long search_end)
{
    unsigned long long int max_val = pow(10, digits);
    unsigned long long int max_paly = 0;
    for (unsigned long long int loop_iterator = 1; loop_iterator <= max_val; ++loop_iterator)
    {
        for (unsigned long long int i = search_begin; i <= search_end; ++i)
        {
            unsigned  long long int test_pally = loop_iterator * i;
            unsigned long long int inverse_pally = test_pally;
            unsigned long long int assembled_num = 0;
            int curr_bit = 0;
            int pow_op = log10(test_pally);
            while (inverse_pally)
            {
                curr_bit = inverse_pally % 10;
                inverse_pally /= 10;
                assembled_num += (static_cast<unsigned long long>(curr_bit) * pow(10, pow_op));

                pow_op--;

            }
            if (assembled_num == test_pally && max_paly < assembled_num)
            {
                max_paly = assembled_num;

            }


        }


    }

    return max_paly;

}
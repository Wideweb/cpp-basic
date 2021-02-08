#include <cassert>
#include <iostream>

#include "my_math.hpp"

int main() {
    double result = my_sqrt(4, 2);
    std::cout << "the 2th root of 4 is " << result << std::endl;
    assert(is_equal(result, 2));

    result = my_sqrt(8, 3);
    std::cout << "the 3th root of 8 is " << result << std::endl;
    assert(is_equal(result, 2));

    result = my_sqrt(625, 4);
    std::cout << "the 4th root of 625 is " << result << std::endl;
    assert(is_equal(result, 5));

    result = my_sqrt(1024, 10);
    std::cout << "the 10th root of 1024 is " << result << std::endl;
    assert(is_equal(result, 2));

    std::cout << "ALL TESTS PASSED!";
}
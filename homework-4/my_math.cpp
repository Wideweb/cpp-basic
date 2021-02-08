#include "my_math.hpp"

bool is_equal(double a, double b) {
    double sub = a - b;
    sub = sub < 0 ? -sub : sub;
    return sub < c_Epsilon;
}
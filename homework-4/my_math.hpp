#include <type_traits>

constexpr double c_Epsilon = 0.0001;

bool is_equal(double a, double b);

template <typename T1, typename T2,
          typename = std::enable_if_t<std::is_arithmetic_v<T1>>,
          typename = std::enable_if_t<std::is_integral_v<T2>>>
double my_pow(T1 basis, T2 exponent) {
    double result = 1.0;
    bool negative = exponent < 0;

    if (negative) {
        exponent *= -1;
    }

    for (int i = 0; i < exponent; i++) {
        if (negative) {
            result /= basis;
        } else {
            result *= basis;
        }
    }

    return result;
}

// https://en.wikipedia.org/wiki/Nth_root#Using_Newton's_method
template <typename T1, typename T2,
          typename = std::enable_if_t<std::is_arithmetic_v<T1>>,
          typename = std::enable_if_t<std::is_integral_v<T2>>>
double my_sqrt(T1 value, T2 exponent) {
    double x = value;

    while (!is_equal(my_pow(x, exponent), value)) {
        x = (1.0 / exponent) *
            ((exponent - 1.0) * x + value / my_pow(x, exponent - 1));
    }

    return x;
}
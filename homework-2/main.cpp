#include <iostream>

int my_abs(int num) { return num < 0 ? num * -1 : num; }

int min(int a, int b) { return a > b ? b : a; }

int rectangleArea(int width, int height) { return width * height; }

double my_pow(double basis, double exponent) {
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

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }

    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {}
#include <iostream>

// Вывести числа от 10 до a по порядку
void task1() {
    int a = 0;
    std::cin >> a;

    int i = 10;
    int step = a > i ? 1 : -1;

    while (i != a + step) {
        std::cout << i << std::endl;
        i += step;
    }
}

// Вывести числа от a до 0
void task2() {
    int a = 0;
    std::cin >> a;

    int target = 0;
    int step = a >= target ? -1 : 1;

    while (target + step != a) {
        std::cout << a << std::endl;
        a += step;
    }
}

// Вывести все числа, на которые делится a без остатка
void task3() {
    int a = 0;
    std::cin >> a;

    int i = 1;
    a = a < 0 ? a * -1 : a;

    while (i <= a + 1) {
        if (a % i == 0) {
            std::cout << i << std::endl;
        }
        ++i;
    }
}

// Вывести a пять раз если оно четное или 3 раза если нечетное
void task4() {
    int a, i = 0;
    std::cin >> a;

    if (a % 2 == 0) {
        while (i < 5) {
            std::cout << a << std::endl;
            ++i;
        }
    } else {
        while (i < 3) {
            std::cout << a << std::endl;
            ++i;
        }
    }
}

// Вывести число 1 столько раз, сколько цифр в a
void task5() {
    int a = 0;
    std::cin >> a;

    do {
        std::cout << 1;
        a /= 10;
    } while (a > 0);
    std::cout << std::endl;
}

// Вывести сколько троек содержит число (число 123 - содержит одну, а 134323 -
// три тройки)
void task6() {
    int a, last_digit = 0;
    std::cin >> a;

    while (a > 0) {
        last_digit = a % 10;

        if (last_digit == 3) {
            std::cout << 3;
        }

        a /= 10;
    }
    std::cout << std::endl;
}

// Вывести число a в обратном порядке
void task7() {
    int a = 0;
    std::cin >> a;

    while (a > 0) {
        std::cout << a % 10;
        a /= 10;
    }
    std::cout << std::endl;
}

// Вывести сколько раз 2-ку нужно умножить саму на себя, чтобы примерно получить
// число a
void task8() {
    int a, i = 0;
    std::cin >> a;

    while (a > 1) {
        ++i;
        a /= 2;
    };
    std::cout << i << std::endl;
}

// Вывести сколько раз нужно число умножить на 2, чтобы a стало больше миллиона
void task9() {
    int a, i = 0;
    std::cin >> a;

    while (a <= 1000000) {
        ++i;
        a *= 2;
    };
    std::cout << i << std::endl;
}

// Ввести число в двоичной системе счисления, вывести в 10-ой
void task10() {
    int value = 0;
    size_t bits_number = sizeof(value) * 8;

    std::cin >> value;
    int decimal = value;
    bool negative = value < 0;
    if (negative) {
        value *= -1;
    }

    std::cout << "binary: " << (negative ? "1" : "0");
    size_t i = 1;
    do {
        size_t shift = bits_number - i - 1;
        std::cout << ((value >> shift) & 0x01);
        ++i;
    } while (i < bits_number);

    std::cout << std::endl;
    std::cout << "decimal: " << decimal << std::endl;
}

int main() { task10(); }
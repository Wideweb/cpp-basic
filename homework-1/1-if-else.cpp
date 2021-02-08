#include <iostream>

// Создать переменную a типа int, ввести с клавиатуры в неё значение, вывести на
// экран положительное это число или отрицательное.
void task1() {
    int a = 0;
    std::cin >> a;

    if (a < 0) {
        std::cout << "negative" << std::endl;
    } else {
        std::cout << "positive" << std::endl;
    }
}

// Вывести на экран чётное это число или нет
void task2() {
    int a = 0;
    std::cin >> a;

    if (a & 0x01) {
        std::cout << "odd" << std::endl;
    } else {
        std::cout << "even" << std::endl;
    }
}

// Вывести на экран двузначное ли это число или нет
void task3() {
    int a = 0;
    std::cin >> a;

    if (a >= 10 && a <= 99) {
        std::cout << "two-digit" << std::endl;
    } else {
        std::cout << "not two-digit" << std::endl;
    }
}

// Вывести на экран: входит ли это число в диапазон чисел от -100 до 100
void task4() {
    int a = 0;
    std::cin >> a;

    if (a >= -100 && a <= 100) {
        std::cout << "in [-100, 100]" << std::endl;
    } else {
        std::cout << "out of [-100, 100]" << std::endl;
    }
}

// Вывести на экран делится ли это число на 3 и на 5
void task5() {
    int a = 0;
    std::cin >> a;

    if (a % 15 == 0) {
        std::cout << "divisible by 3 and 5" << std::endl;
    } else {
        std::cout << "not divisible by 3 and 5" << std::endl;
    }
}

// Вывести на экран делится ли это число на 2 или на 7
void task6() {
    int a = 0;
    std::cin >> a;

    bool byTwo = a % 2 == 0;
    bool bySeven = a % 7 == 0;

    if (byTwo) {
        std::cout << "divisible by 2" << std::endl;
    }

    if (bySeven) {
        std::cout << "divisible by 7" << std::endl;
    }

    if (!byTwo && !bySeven) {
        std::cout << "not divisible by 2 or 7" << std::endl;
    }
}

// Вывести на экран это число отрицательным если оно было положительным или
// положительным, если было отрицательным
void task7() {
    int a = 0;
    std::cin >> a;

    std::cout << a * -1 << std::endl;
}

// Если число больше 1000 вывести его, разделив на 10
void task8() {
    int a = 0;
    std::cin >> a;

    if (a > 1000) {
        a = a / 10;
    }

    std::cout << a << std::endl;
}

// Если последняя цифра числа 3, то прибавить ко всему числу 1, разделить на 2 и
// вывести результат
void task9() {
    int a = 0;
    std::cin >> a;

    if (a % 10 == 3) {
        a = (a + 1) / 2;
    }

    std::cout << a << std::endl;
}

// Если число больше 100 - заменить предпоследнюю цифру(разряд десятков) на 8 и
// вывести результат
void task10() {
    int a = 0;
    std::cin >> a;

    if (a > 100) {
        int units = a % 10;
        a = (a / 100) * 100 + 80 + units;
    }

    std::cout << a << std::endl;
}

int main() { task10(); }
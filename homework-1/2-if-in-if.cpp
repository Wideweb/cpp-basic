#include <iostream>
#include <string>

// Создать ещё переменную int b и ввести с клавиатуры её значение, если a -
// положительное, проверить положительное ли b и вывести их сумму, если b
// отрицательное - вывести их разность. В случае если a отрицательное, проверить
// положительное ли b и вывести их произведение, если b отрицательное - вывести
// частное a на b
void task1() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a >= 0) {

        if (b >= 0) {
            std::cout << a + b << std::endl;
        } else {
            std::cout << a - b << std::endl;
        }

    } else {

        if (b >= 0) {
            std::cout << a * b << std::endl;
        } else {
            std::cout << a / b << std::endl;
        }
    }
}

//Если a нечетное, то проверить четное ли b и сообщить об этом пользователю,
//если же a чётное, то ничего не выводить на экран
void task2() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a % 2 != 0) {
        if (b % 2 == 0) {
            std::cout << "b is even" << std::endl;
        } else {
            std::cout << "b is odd" << std::endl;
        }
    }
}

//Если a больше 0 и меньше 10, проверить: является ли b меньше чем a и сообщить
//результат. Если же a меньше 0 или больше 10, то проверить больше ли b 100 и
//вывести результат на экран
void task3() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a > 0 && a < 10) {

        if (b < a) {
            std::cout << "b is less than a" << std::endl;
        } else {
            std::cout << "b isn't less than a" << std::endl;
        }

    } else {
        if (b > 100) {
            std::cout << "b is bigger than 100" << std::endl;
        } else {
            std::cout << "b isn't bigger than 100" << std::endl;
        }
    }
}

// Если b меньше a проверить, является ли b положительным, если b больше a,
// проверить, является ли a положительным, результат вывести на экран
void task4() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (b < a) {
        if (b >= 0) {
            std::cout << "b is positive" << std::endl;
        } else {
            std::cout << "b is negative" << std::endl;
        }
    } else if (b > a) {
        if (a >= 0) {
            std::cout << "a is positive" << std::endl;
        } else {
            std::cout << "a is negative" << std::endl;
        }
    }
}

// Если a делится на b без остатка - вывести четное ли b, если a не делиться на
// b без остатка, проверить четное ли a
void task5() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a % b == 0) {
        if (b % 2 == 0) {
            std::cout << "b is even" << std::endl;
        } else {
            std::cout << "b is odd" << std::endl;
        }
    } else {
        if (a % 2 == 0) {
            std::cout << "a is even" << std::endl;
        } else {
            std::cout << "a is odd" << std::endl;
        }
    }
}

// Если a не равно нулю и при этом меньше b, то вывести удвоенное b. В случае
// если b меньше 100 и больше 10 -  утроенное.  Вывести просто b в остальных
// случаях. Если же а равно нулю или больше b - ничего не делать
void task6() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a != 0 && a < b) {
        if (b > 10 && b < 100) {
            std::cout << b * b * b << std::endl;
        } else {
            std::cout << b * b << std::endl;
        }
    } else if (a == b) {
        std::cout << b << std::endl;
    }
}

// Если a входит в диапазон чисел от -100 до 100 включительно, при этом является
// нечётным числом и его последняя цифра не равна 1, то вывести является ли b
// таким же числом или нет(т.е. проверить на те же условия, что и а)
void task7() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    auto check = [](int x) {
        return x >= -100 && x <= 100 && x % 2 == 1 && x % 10 != 1;
    };

    if (check(a)) {
        std::cout << (check(b) ? "true" : "false") << std::endl;
    }
}

// Если a делится на 3 и на 5, проверить b на четность и если b четное, то
// умножить его на a в случае если a меньше 100, или сложить с a в другом
// случае. А если b нечетное, то вывести разность a и b. Если же a не делится ни
// на 3 ни на 5, то сообщить об этом и вслед вывести b
void task8() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a % 15 == 0) {
        if (b % 2 == 0) {
            if (a < 100) {
                std::cout << a * b << std::endl;
            } else {
                std::cout << a + b << std::endl;
            }
        } else {
            std::cout << a - b << std::endl;
        }
    } else {
        std::cout << "a is not divisible by 3 and 5" << std::endl;
        std::cout << "b is " << b << std::endl;
    }
}

// Если a больше 10 и меньше 80, то в случае, если ещё и a < b и b не равно 66 -
// вывести сумму a и b. Если же a > b и a не равен 44 - вывести разность a и b,
// а в случае если a равно 44 или 66 - вывести a деленое на 2. В других случаях
// - ничего не делать
void task9() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    if (a > 10 && a < 80) {
        if (a < b && b != 66) {
            std::cout << a + b << std::endl;
        } else if (a > b && a != 44) {
            std::cout << a - b << std::endl;
        } else if (a == 44 || a == 66) {
            std::cout << a / 2 << std::endl;
        }
    }
}

// В случае, если a и b - положительные, проверить четные ли эти числа, нечетные
// ли они, делятся ли на 5, делятся ли на 7, и вывести результат, а так же
// написать кто из них больше другого. В случае если a и b - отрицательные,
// проверить: меньше ли каждый из них -100, меньше ли (-17 и одновременно больше
// ли -130), больше ли их произведение 15000

void task10() {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    auto divisionCheck = [](std::string name, int value) {
        if (value % 2 == 0) {
            std::cout << name << " is even" << std::endl;
        } else {
            std::cout << name << " is odd" << std::endl;
        }

        if (value % 5 == 0) {
            std::cout << name << " is divisible by 5" << std::endl;
        } else {
            std::cout << name << " is not divisible by 5" << std::endl;
        }

        if (value % 7 == 0) {
            std::cout << name << " is divisible by 7" << std::endl;
        } else {
            std::cout << name << " is not divisible by 7" << std::endl;
        }
    };

    auto valueCheck = [](std::string name, int value) {
        if (value < -100) {
            std::cout << name << " is less than -100" << std::endl;
        } else {
            std::cout << name << " is not less than -100" << std::endl;
        }

        if (value < -17 && value > -130) {
            std::cout << name << " is less than -17 and bigger than -130"
                      << std::endl;
        } else {
            std::cout << name << " is not less than -17 and bigger than -130"
                      << std::endl;
        }
    };

    if (a >= 0 && b >= 0) {
        divisionCheck("a", a);
        divisionCheck("b", b);
    }

    if (a < 0 && b < 0) {
        valueCheck("a", a);
        valueCheck("b", b);

        if (a * b > 15000) {
            std::cout << " the product is bigger than 15000" << std::endl;
        }
    }
}

int main() { task10(); }
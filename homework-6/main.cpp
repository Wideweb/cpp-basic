#include <iostream>

// Инициализировать 4 переменных значением 123 в двоичном(bin), десятичном(dec),
// шестнадцатеричном(hex), восьмеричном(oct) представлениях (системах счисления)
// и вывести их на экран.
// cout:
// bin: 123
// dec: 123
// hex: 123
// oct: 123
void task_1() {
    int bin = 0b1111011;
    int dec = 123;
    int hex = 0x7B;
    int oct = 0173;

    std::cout << "bin: " << bin << std::endl;
    std::cout << "dec: " << dec << std::endl;
    std::cout << "hex: " << hex << std::endl;
    std::cout << "oct: " << oct << std::endl;
}

// Создать массив char’ов или указатель на строку "Hello\ba\nr", вывести эту
// строку на экран, что оно выведет и почему?
// \b - возврат на шаг
// \n - перевод строки
void task_2() {
    char str[10] = "Hello\ba\nr";
    std::cout << str << std::endl;
}

// Инициализируйте переменную числом 9000000000 и выведите её на экран
void task_3() {
    unsigned long long int v = 9'000'000'000;
    std::cout << v << std::endl;
}

// Инициализируйте переменную числом 18446744073709551615 и выведите её на
// экран, так, чтобы компилятор не кидал предупреждение.
void task_4() {
    unsigned long long int v = 18'446'744'073'709'551'615u;
    std::cout << v << std::endl;
}

// Сравнить два числа 18446700000000000.5 и 18446700000000000.4 на равенство,
// ответ должен быть 0 (false).
void task_5() {
    char a[20] = "18446700000000000.5";
    char b[20] = "18446700000000000.4";

    for (int i = 0; i < 19; i++) {
        if (a[i] != b[i]) {
            std::cout << "false" << std::endl;
            return;
        }
    }

    std::cout << "true" << std::endl;
}

// Создать три переменные char, запросить у пользователя ввести в каждую из этих
// переменных символ, если эти символы ‘a’, ’b’ и ‘c’ (в любом порядке) -
// вывести на экран “ABC”, иначе “NO\ABC”
void task_6() {
    char a, b, c;
    std::cout << "a: " << std::endl;
    std::cin >> a;
    std::cout << "b: " << std::endl;
    std::cin >> b;
    std::cout << "c: " << std::endl;
    std::cin >> c;

    const auto check = [](char x) { return x >= 'a' && x <= 'c'; };

    if (check(a) && check(b) && check(c)) {
        std::cout << "ABC" << std::endl;
    } else {
        std::cout << "NO ABC" << std::endl;
    }
}

// Запросить у пользователя ввести число от 1 до 10, вывести на экран словом это
// число, в зависимости от выбранного (“one”, “two” и т.д.), если ввел не то,
// вывести “Obidul’ki:(”
void task_7() {
    int a;
    std::cout << "enter from 1 to 10: " << std::endl;
    std::cin >> a;

    switch (a) {
    case 1:
        std::cout << "one" << std::endl;
        break;
    case 2:
        std::cout << "two" << std::endl;
        break;
    case 3:
        std::cout << "three" << std::endl;
        break;
    case 4:
        std::cout << "four" << std::endl;
        break;
    case 5:
        std::cout << "five" << std::endl;
        break;
    case 6:
        std::cout << "six" << std::endl;
        break;
    case 7:
        std::cout << "seven" << std::endl;
        break;
    case 8:
        std::cout << "eight" << std::endl;
        break;
    case 9:
        std::cout << "nine" << std::endl;
        break;
    case 10:
        std::cout << "ten" << std::endl;
        break;

    default:
        std::cout << "Obidul’ki:(" << std::endl;
        break;
    }
}

// Предложить пользователю ввести положительное число. Если он введет другое -
// повторять эту просьбу, пока не исправится.
void task_8() {
    int a;

    do {
        std::cout << "enter positive number:" << std::endl;
        std::cin >> a;
    } while (a < 0);
}

// Создать массив из 1000 целых чисел, заполнить его последовательностью от 1000
// до 2000
void task_9() {
    int arr[1000];

    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 + i;
    }

    for (int i = 0; i < 1000; i++) {
        std::cout << arr[i] << std::endl;
    }
}

// Создать двумерный массив 100 на 200 и заполнить его последовательностью чисел
// от 1 до 20000
void task_10() {
    const int h = 100;
    const int w = 200;

    int arr[h][w];

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            arr[i][j] = i * w + j;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cout << arr[i][j] << std::endl;
        }
    }
}

// Создать в динамической памяти массив из 10 целых чисел, заполнить его четными
// числами от 2, затем удалить и попробовать вывести массив на экран через его
// указатель(почему такой результат?)
void task_11() {
    int *arr = new int[10];

    for (int i = 0; i < 10; i++) {
        arr[i] = (i + 1) * 2;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    // result: 2 4 6 8 10 12 14 16 18 20

    delete[] arr;

    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    // result: 2 4 6 8 10 12 14 16 18 20
    // Память была освобождена, но никто не успел её перезаписать новыми
    // значениями.
}

// Создать динамический двумерный массив 4 на 3, заполнить его
// последовательностью от 1 до 12 и вывести
void task_12() {
    const int h = 4;
    const int w = 3;

    int **arr = new int *[h];

    for (int i = 0; i < h; i++) {
        arr[i] = new int[w];
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            arr[i][j] = i * w + j + 1;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cout << arr[i][j] << std::endl;
        }
    }

    for (int i = 0; i < h; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() { task_12(); }

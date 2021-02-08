#include <assert.h>
#include <iostream>

// Создать в стеке переменную a типа float, и указатель b на неё. Пользуясь
// только b, изменить значение переменной a на 1.618 и вывести на экран.
void task1() {
    float a;
    float *b = &a;
    *b = 1.618f;

    assert(a == 1.618f);
}

// Создать третью переменную c и занести в нее адрес b из предыдущей задачи.
// Через c изменить значение a на 3.141 и также вывести на экран.
void task2() {
    float a;
    float *b = &a;
    *b = 1.618f;

    float **c = &b;

    **c = 3.141f;

    assert(a == 3.141f);
}

// Создать функцию принимающую адрес float, и округляющую по математическим
// правилам число, адрес которой в эту функцию будет передан. (Т.е. если
// передать в эту функцию адрес переменной a со значением 3.141, после
// выполнения функции в a будет число 3) Функция ничего не должна возвращать
void round(float *value) {
    int integer_part = int(*value);
    int fractional_part = int(*value * 10) % 10;

    *value = float(integer_part);

    if (fractional_part >= 5) {
        ++(*value);
    }
}

void task3() {
    float value = 1.5;
    round(&value);
    assert(value == 2.0f);

    value = 1.49;
    round(&value);
    assert(value == 1.0f);

    value = 1.51;
    round(&value);
    assert(value == 2.0f);
}

// Создать массив из 7 char, инициализировать его значениями “Memphis”.
// Сохранить адрес третьего элемента (символа) в переменной d. Через эту
// переменную изменить значение элемента на 't’. Вывести массив на экран.
void task4() {
    char str[7] = {'M', 'e', 'm', 'p', 'h', 'i', 's'};
    char *d = str + 2;
    *d = 't';

    for (size_t i = 0; i < 7; ++i) {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

void task5() {
    // char str_1[7] = {'M', 'e', 'm', 'p', 'h', 'i', 's'};
    // cout: Memthis\xa0\xfd\xbf\xef\xfe\x7f

    // char str_2[8] = "Memthis";
    // cout: Memthis

    // Так как у str_2 есть последний дополнительный байт, который хранит ноль
    // (\0). Cout останавливает вывод строки, когда встречает байт с нулевым
    // значением.
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void task6() {
    int a = 1;
    int b = 2;

    swap(&a, &b);
    assert(a == 2);
    assert(b == 1);
}

enum class SortOrder { Asc = 0, Desc = 1 };

// Функция сортировки массива, функция принимает указатель на массив и размер и
// ничего не возвращает.
void sort(int *array, size_t size, SortOrder order = SortOrder::Asc) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {

            if (order == SortOrder::Asc) {
                if (array[i] > array[j]) {
                    swap(array + i, array + j);
                }
            }

            if (order == SortOrder::Desc) {
                if (array[i] < array[j]) {
                    swap(array + i, array + j);
                }
            }
        }
    }
}

void task7() {
    int arr[10] = {5, 9, 1, 3, 7, 6, 4, 2, 8, 0};

    std::cout << "Ascending Order:" << std::endl;
    sort(arr, 10, SortOrder::Asc);
    for (size_t i = 0; i < 10; ++i) {
        std::cout << arr[i] << std::endl;
    }

    std::cout << "Descending Order:" << std::endl;
    sort(arr, 10, SortOrder::Desc);
    for (size_t i = 0; i < 10; ++i) {
        std::cout << arr[i] << std::endl;
    }
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
}
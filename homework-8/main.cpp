#include <iostream>

class Rect {
    unsigned int w;
    unsigned int h;

  public:
    Rect(unsigned int w, unsigned int h) : w(w), h(h) {}

    void show() {
        std::cout << "width: " << w << " height: " << h << std::endl;
    }

    bool operator==(const Rect &other) { return other.w == w && other.h == h; }

    void operator+=(unsigned int delta) {
        w += delta;
        h += delta;
    }

    Rect operator+(const Rect &other) { return {w + other.w, h + other.h}; }
    Rect operator-(const Rect &other) { return {w - other.w, h - other.h}; }
    Rect operator*(const Rect &other) { return {w * other.w, h * other.h}; }
};

void task1() {
    Rect obj(1, 3);
    obj.show(); //выводит размер в cout
    Rect obj2 = obj;
    if (obj2 == obj) {
        std::cout << "rectangles are equal" << std::endl;
    }
    obj += 4;
    if (obj2 == obj) {
        std::cout << "rectangles are equal" << std::endl;
    }
}

void task2() {
    Rect obj1{10, 10};
    Rect obj2{5, 5};
    Rect obj3{3, 3};
    Rect obj4{4, 4};

    Rect obj = obj1 + obj2 - obj3 * obj4;
    obj.show();
}

int main() {
    task1();
    task2();
}

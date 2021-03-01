#include <cmath>
#include <iostream>

// Напишите 3 класса: прямоугольник, треугольник и круг.
// У каждого из них должен быть конструктор принимающий аргументы длин сторон
// и радиуса, соответственно. · У каждого класса есть метод вычисляющий площадь
// фигуры. Расширьте эти классы наследниками параллелепипед, призма
// (треугольная), и цилиндр, добавив в каждый из этих классов метод вычисляющий
// объем. Этот метод должен воспользоваться унаследованным методом вычисления
// площади. В комментарии (прямо в коде, не обязательно на английском)) напишите
// почему при наследовании вы выбрали именно такой ключ доступа (public, private
// или protected наследование)

const double c_PI = 3.14;

class Rect {
  protected:
    unsigned int m_Width;
    unsigned int m_Height;

  public:
    Rect(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {}

    unsigned int area() { return m_Width * m_Height; }
};

class Triangle {
  protected:
    unsigned int m_Side1;
    unsigned int m_Side2;
    unsigned int m_Side3;

  public:
    Triangle(unsigned int side1, unsigned int side2, unsigned int side3)
        : m_Side1(side1), m_Side2(side2), m_Side3(side3) {}

    unsigned int area() {
        unsigned int p = (m_Side1 + m_Side2 + m_Side3) / 2;
        return std::sqrt(p * (p - m_Side1) * (p - m_Side2) * (p - m_Side3));
    }
};

class Circle {
  protected:
    unsigned int m_Radius;

  public:
    Circle(unsigned int radius) : m_Radius(radius) {}

    unsigned int area() { return c_PI * m_Radius * m_Radius; }
};

class Parallelepiped : private Rect {
    // Площадь параллелепипеда отличается от площади прямоугольника, поэтому мы
    // закрываем к ней доступ для внешнего пользования и использования в
    // дочерних классах параллелепипеда.
  private:
    unsigned int m_Depth;

  public:
    Parallelepiped(unsigned int width, unsigned int height, unsigned int depth)
        : Rect(width, height), m_Depth(depth) {}

    unsigned int volume() { return m_Depth * area(); }
};

class Prism : private Triangle {
    // Площадь призмы отличается от площади треугольника, поэтому мы закрываем к
    // ней доступ для внешнего пользования и использования в дочерних классах
    // призмы.
  private:
    unsigned int m_Height;

  public:
    Prism(unsigned int side1, unsigned int side2, unsigned int side3,
          unsigned int height)
        : Triangle(side1, side2, side3), m_Height(height) {}

    unsigned int volume() { return m_Height * area(); }
};

class Cylinder : private Circle {
    // Площадь цилиндра отличается от площади круга, поэтому мы закрываем к
    // ней доступ для внешнего пользования и использования в дочерних классах
    // цилиндра.
  private:
    unsigned int m_Height;

  public:
    Cylinder(unsigned int radius, unsigned int height)
        : Circle(radius), m_Height(height) {}

    unsigned int volume() { return m_Height * area(); }
};

int main() {
    Rect rect{4, 5};
    std::cout << "Rect area: " << rect.area() << std::endl;

    Triangle triangle{3, 4, 5};
    std::cout << "Triangle area: " << triangle.area() << std::endl;

    Circle circle{10};
    std::cout << "Circle area: " << circle.area() << std::endl;

    Parallelepiped parallelepiped{4, 5, 10};
    std::cout << "Parallelepiped volume: " << parallelepiped.volume()
              << std::endl;

    Prism prism{3, 4, 5, 10};
    std::cout << "Prism volume: " << prism.volume() << std::endl;

    Cylinder cylinder{10, 10};
    std::cout << "Cylinder volume: " << cylinder.volume() << std::endl;
}

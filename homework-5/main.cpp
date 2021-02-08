#include <cassert>
#include <iostream>

#include "shapes.hpp"

int main() {
    Triangle triangle = {{1.0, 1.0}, {3.0, 5.0}, {5.0, 1.0}};
    Point point;

    // Point inside triangle
    point = {3.0, 3.0};
    assert(is_collide(point, triangle) == true && "Test 1 failed.");

    // Point under triangle
    point = {3.0, 0.5};
    assert(is_collide(point, triangle) == false && "Test 2 failed.");

    // Point above triangle
    point = {3.0, 6.0};
    assert(is_collide(point, triangle) == false && "Test 3 failed.");

    // Point is to the left of triangle
    point = {2.0, 4.0};
    assert(is_collide(point, triangle) == false && "Test 4 failed.");

    // Point is to the right of triangle
    point = {4.0, 4.0};
    assert(is_collide(point, triangle) == false && "Test 5 failed.");

    // Point on the bottom edge of a triangle
    point = {2.0, 1.0};
    assert(is_collide(point, triangle) == true && "Test 6 failed.");

    // Point on the right edge of a triangle
    point = {4.0, 3.0};
    assert(is_collide(point, triangle) == true && "Test 7 failed.");

    // Point on the left edge of a triangle
    point = {2.0, 3.0};
    assert(is_collide(point, triangle) == true && "Test 8 failed.");

    // Point on triangle corner
    point = {5.0, 1.0};
    assert(is_collide(point, triangle) == true && "Test 9 failed.");

    std::cout << "All Tests Passed!" << std::endl;
}
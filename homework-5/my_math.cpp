#include "my_math.hpp"

Vec2 Vec2::operator-(const Vec2 &v) const { return {x - v.x, y - v.y}; }

Vec2 Vec2::normal() const { return {-y, x}; }

double Vec2::dot(const Vec2 &v) const { return x * v.x + y * v.y; }
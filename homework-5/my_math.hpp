#pragma once

struct Vec2 {
    double x;
    double y;

    Vec2 operator-(const Vec2 &v) const;

    Vec2 normal() const;

    double dot(const Vec2 &v) const;
};
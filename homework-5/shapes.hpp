#pragma once

#include "my_math.hpp"

using Point = Vec2;

// Separating Axis Theorem. If an axis can be found along witch the projection
// of two convex shapes do not overlap, then two shapes do not intersect at all.
template <unsigned int TSize>
bool is_collide(const Point &point, const Point (&vertices)[TSize]) {
    for (unsigned int i = 0; i < TSize; i++) {
        Vec2 axis = (vertices[(i + 1) % TSize] - vertices[i]).normal();
        double p_scalar = axis.dot(point);

        double shape_scalars[TSize];
        for (unsigned int i = 0; i < TSize; i++) {
            shape_scalars[i] = axis.dot(vertices[i]);
        }

        double shape_min_scalar = shape_scalars[0];
        double shape_max_scalar = shape_scalars[0];
        for (unsigned int i = 1; i < TSize; i++) {
            if (shape_scalars[i] < shape_min_scalar) {
                shape_min_scalar = shape_scalars[i];
            }

            if (shape_scalars[i] > shape_max_scalar) {
                shape_max_scalar = shape_scalars[i];
            }
        }

        if (p_scalar > shape_max_scalar || p_scalar < shape_min_scalar) {
            return false;
        }
    }

    return true;
}

using Triangle = Point[3];
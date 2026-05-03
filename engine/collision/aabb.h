#pragma once

namespace pf {

struct Aabb {
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;
    float h = 0.0f;

    float left() const {
        return x;
    }

    float right() const {
        return x + w;
    }

    float top() const {
        return y;
    }

    float bottom() const {
        return y + h;
    }
};

inline bool overlaps(const Aabb& a, const Aabb& b) {
    return a.left() < b.right() &&
           a.right() > b.left() &&
           a.top() < b.bottom() &&
           a.bottom() > b.top();
}

}

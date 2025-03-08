#include "Vec2.h"
#include <cmath>

Vec2::Vec2() {}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

bool Vec2::operator==(const Vec2 &rhs) const {
    return (x == rhs.x && x == rhs.y);
}

bool Vec2::operator!=(const Vec2 &rhs) const {
    return (x != rhs.x && x != rhs.y);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 Vec2::operator-(const Vec2 &rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator/(const float val) const { return Vec2(x / val, y / val); }

Vec2 Vec2::operator*(const float val) const { return Vec2(x * val, y * val); }

void Vec2::operator+=(const Vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
}
void Vec2::operator-=(const Vec2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator/=(const float val) {
    x /= val;
    y /= val;
}

void Vec2::operator*=(const float val) {
    x *= val;
    y *= val;
}

float Vec2::dist(const Vec2 &rhs) const {
    Vec2 result = *this - rhs;
    return result.length();
}

float Vec2::length() const { return std::sqrt((x * x) + (y * y)); }

void Vec2::normalize() {
    x /= x;
    y /= y;
}

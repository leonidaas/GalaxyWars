#pragma once
#include "Vec2.h"

#include <SFML/Graphics.hpp>
#include <ios>

class Component {
public:
    bool exists = false;
};

class CCollision : public Component {
public:
    float radius = 0;

    CCollision() = default;
    CCollision(float r) : radius(r) {}
};

enum EInput { UP, DOWN, LEFT, RIGHT, SHOOT, IDLE };

class CInput : public Component {
public:
    int up = false;
    int down = false;
    int left = false;
    int right = false;
    int shoot = false;

    EInput currentInput = EInput::IDLE;

    CInput() = default;
};

class CLifespan : public Component {
public:
    int lifespan = 0;
    int remaining = 0;

    CLifespan() = default;
    CLifespan(int totalLifeSpan)
        : lifespan(totalLifeSpan), remaining(totalLifeSpan) {}
};

class CScore : public Component {
public:
    int score = 0;

    CScore() = default;
    CScore(int s) : score(s) {}
};

class CShape : public Component {
public:
    sf::CircleShape circle;

    CShape() = default;
    CShape(float radius, size_t points, const sf::Color &fill,
           const sf::Color &outline, float thickness)
        : circle(radius, points) {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin({radius, radius});
    }
};

class CTransform : public Component {
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 velocity = {0.0, 0.0};
    // Vec2 scale = 1;
    float angle = 0;

    CTransform() = default;
    CTransform(const Vec2 &p, const Vec2 &v, float a)
        : pos(p), velocity(v), angle(a) {}
};

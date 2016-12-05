#include "Vector2.h"
#include <math.h>

Vector2::Vector2(double x, double y)
{
        this->x = x;
        this->y = y;
}

Vector2::Vector2() {

    this->x = 0;
    this->y = 0;

}

Vector2::~Vector2()
{
    //dtor
}


Vector2 Vector2::normalize() {

    double len = this->len();
    if (len > 0) {
        x/=len;
        y/=len;
    }
    return *this;
}
Vector2 Vector2::reverse() {

    x = -x;
    y = -y;

    return *this;
};
Vector2 Vector2::rotate(double r) {

    double x2 = x;
    double y2 = y;

    x = x2 * cos(r) - y2 * sin(r);
    y = x2 * sin(r) + y2 * cos(r);

    return *this;

};

double Vector2::len() {

    return sqrt(x*x + y*y);

}


Vector2 Vector2::add(Vector2 other) {

    x += other.x;
    y += other.y;
    return *this;

}
Vector2 Vector2::sub(Vector2 other) {

    x -= other.x;
    y -= other.y;
    return *this;

}
Vector2 Vector2::scale(double s) {

    x *= s;
    y *= s;
    return *this;
}
Vector2 Vector2::perp() {

    double x2 = x;
    x = y;
    y = -x2;
    return *this;
}
double Vector2::dot(Vector2 other) {
    return x * other.x + y * other.y;
}

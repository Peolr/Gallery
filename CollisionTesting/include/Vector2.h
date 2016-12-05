#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2
{
    public:
        Vector2();
        Vector2(double x, double y);
        virtual ~Vector2();
        double x;
        double y;

        Vector2 normalize();
        Vector2 reverse();
        Vector2 rotate(double r);
        Vector2 add(Vector2 other);
        Vector2 sub(Vector2 other);
        Vector2 scale(double s);
        Vector2 perp();

        double dot(Vector2 other);
        double len();

    protected:

    private:
};

#endif // VECTOR2_H

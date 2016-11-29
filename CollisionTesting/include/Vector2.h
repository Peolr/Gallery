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

        void normalize();
        void reverse();
        void rotate(double r);
        void add(Vector2 other);
        void sub(Vector2 other);
        void scale(double s);
        void perp();

        double dot(Vector2 other);
        double len();

    protected:

    private:
};

#endif // VECTOR2_H

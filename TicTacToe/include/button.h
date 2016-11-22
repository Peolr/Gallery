#ifndef BUTTON_H
#define BUTTON_H


class button
{
    public:
        button();
        button(int x, int y, int w, int h);
        virtual ~button();

        int x;
        int y;
        int w;
        int h;

        int who;

    protected:

    private:
};

#endif // BUTTON_H

#ifndef SAVE_H
#define SAVE_H

#include <string>
#include <Polygon.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>

std::stringstream encode(int i);
std::stringstream encode(double i);

int decodeI(char* s);
double decodeD(char* s);

class Save
{
    public:
        Save(std::string p);
        virtual ~Save();

        std::string path;

        std::fstream stream;

        std::string loadedStr;

        long int readPos;

        void open();
        void close();

        void writeInt(int i);
        void writeDouble(double i);
        void writeBool(bool i);

        int readInt();
        double readDouble();
        char* read(int s);
        bool readBool();

        void load();

        void writePolygon(Polygon* p);
        bool isOpen();

    protected:

    private:
};

#endif // SAVE_H

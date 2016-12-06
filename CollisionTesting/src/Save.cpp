#include "Save.h"

#include <iostream>
#include <cstring>

std::stringstream cast(void* v) {
    std::stringstream s;
    s.str("");
    char* bits = reinterpret_cast<char*>(v);
    //int a = static_cast<int>(bits);
    for (std::size_t n = 0; n < sizeof v; ++n) {
        s << bits[n];
    }
    return s;
}

std::stringstream encode(void* in) {
    std::stringstream s = cast(in);
    return s;
}


int decodeI(char* c) {
    //char* testc = const_cast<char*>(reinterpret_cast<const char*>(c));
    int testd = *reinterpret_cast<int*>(c);
    std::cout << "dfi: " << testd << std::endl;
    return testd;
}

double decodeD(char* c) {
    //char* testc = const_cast<char*>(reinterpret_cast<const char*>(c));
    double testd = *reinterpret_cast<double*>(c);
    return testd;
}

double decodeB(char* c) {
    //char* testc = const_cast<char*>(reinterpret_cast<const char*>(c));
    bool testd = *reinterpret_cast<bool*>(c);
    std::cout << "dfb: " << testd << std::endl;
    return testd;
}

Save::Save(std::string p)
{
    path = p;

}

Save::~Save()
{
    //dtor
}

void Save::open() {
    stream.open(path, std::fstream::trunc | std::fstream::out | std::fstream::in);
    stream.seekg(0, stream.beg);
    readPos = 0;
}

void Save::close() {
    stream.close();
}

void Save::writeInt(int i) {
    stream << encode(&i).str();
}

void Save::writeDouble(double i) {
    stream << encode(&i).str();
}

void Save::writeBool(bool i) {
    stream << encode(&i).str();
}

void Save::load() {
    stream.seekg (0, stream.end);
    int length = stream.tellg();
    stream.seekg (0, stream.beg);
    char* bf = new char[length];

    stream.read(bf, length);

    std::string s(bf);
    loadedStr = s;
    delete[] bf;
}
char* Save::read(int s) {

    char* bf = new char[s];
    stream.seekg(readPos);
    stream.read(bf, s);

    readPos+=s;

    return bf;
}

int Save::readInt() {
    char* r = read(4);
    int ret = decodeI(r);
    delete[] r;
    return ret;
}

double Save::readDouble() {
    char* r = read(8);
    double ret = decodeD(r);
    delete[] r;
    return ret;
}

bool Save::readBool() {
    char* r = read(4);
    bool ret = decodeB(r);
    delete[] r;
    return ret;
}



bool Save::isOpen() {
    return stream.is_open();
}

void Save::writePolygon(Polygon* p) {

}



#ifndef COLOUR_H
#define COLOUR_H

#include <string>
#include <sstream>
#include <iomanip>

class Colour
{
public:
    Colour(int red, int green, int blue):r(red), g(green), b(blue) {}

    int r;
    int g;
    int b;

    std::string getHexCode() {
        std::stringstream hexStream;
        hexStream << "#";
        hexStream << std::hex << std::setfill('0') << std::setw(2) << r;
        hexStream << std::hex << std::setfill('0') << std::setw(2) << g;
        hexStream << std::hex << std::setfill('0') << std::setw(2) << b;
        return hexStream.str();
    }
};

#endif // COLOUR_H

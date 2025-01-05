#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <cstdint>
#include <math.h>
#include "../Math/Vector3D.hpp"
using namespace std;

#define BLUE 0xffffff 
#define PURPLE 0x8E44AD00
#define ORANGE 0xF39C1200
#define LIGHTBLUE 0xD1F2EB00
#define PINK 0xFF02CD00
#define RED 0xE74C3C00
#define WHITE 0xFFFFFF00
#define LIGHTGREY 0xC6C6C600
#define DARKGREY 0x808B9600


class Color{
private:
    void calculateColor();
public:
    int r,g,b,a;
    uint32_t original;
    Color(){};

    Color(uint32_t color);
    Color(int r,int g,int b,int a);
    Color(int r,int g,int b);
    Color(const Vector3D& v);

    Color blend(const Color& c, double sourcePonderation);
    // Operators
    Color& operator+=(const Color& v);
    Color& operator*=(double t);
    Color& operator/=(double t);

    //      Custom Colors
    static Color Grey(){ return Color(82,84,84);}
    static Color White(){ return Color(255,255,255);}
    static Color Black(){ return Color(0,0,0);}
    static Color Purple(){ return Color(137, 11, 176);}
    static Color Yellow(){ return Color(212, 227, 9);}
    static Color Red(){ return Color(255,0,0);}
    static Color Blue(){ return Color(0,0,255);}
    static Color Green(){ return Color(0,255,0);}
    static Color Orange(){ return Color(255,171,15);}
    static Color LightGreen(){ return Color(15,255,107);}
};

// Color Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Color& c) {
    return out << "Color(rgba): " << c.r << ' ' << c.g << ' ' << c.b << ' ' << c.a;
}

inline Color operator+(const Color& u, const Color& v) {
    return Color(u.r + v.r, u.g + v.g, u.b + v.b, u.a + v.a);
}

inline Color operator-(const Color& u, const Color& v) {
    return Color(u.r - v.r, u.g - v.g, u.b - v.b, u.a - v.a);
}

inline Color operator*(const Color& u, const Color& v) {
    return Color(u.r * v.r, u.g * v.g, u.b * v.b, u.a * v.a);
}

inline Color operator*(double t, const Color& v) {
    t = std::fmax(0,t); // Avoid negative numbers
    return Color(t*v.r, t*v.g, t*v.b, t*v.a);
}

inline Color operator*(const Color& v, double t) {
    return t * v;
}

inline Color operator/(const Color& v, double t) {
    return (1/t) * v;
}




#endif
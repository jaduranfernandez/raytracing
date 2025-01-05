#include "../../include/Visual/Color.hpp"


Color::Color(uint32_t color){
    r = (color >> 24) & 0xFF;
    g = (color >> 16) & 0xFF;
    b = (color >> 8) & 0xFF;
    a = color & 0xFF;
    original = color;
}

Color::Color(int r,int g,int b,int a){
    // Makes sure it has values in range [0, 255]
    this->r = std::fmin(std::abs(r), 255);
    this->g = std::fmin(std::abs(g), 255);
    this->b = std::fmin(std::abs(b), 255);
    this->a = std::fmin(std::abs(a), 255);
    calculateColor();
}

Color::Color(int r,int g,int b): Color(r,g,b,255){

}

Color::Color(const Vector3D& v): Color(v.x, v.y, v.z){

}

void Color::calculateColor(){
    original = (r<<24)+(g<<16)+(b<<8)+a;
}

Color Color::blend(const Color& c, double sourcePonderation){
    sourcePonderation = std::fmin(std::abs(sourcePonderation), 1);
    Color blendedColor = Color(
        (sourcePonderation)*(r) + (1-sourcePonderation)*c.r,
        (sourcePonderation)*(g) + (1-sourcePonderation)*c.g,
        (sourcePonderation)*(b) + (1-sourcePonderation)*c.b,
        (sourcePonderation)*(a) + (1-sourcePonderation)*c.a
    );
    return blendedColor;
}


Color& Color::operator+=(const Color& v) {
    this->r = std::fmin(std::abs(r + v.r), 255);
    this->g = std::fmin(std::abs(g + v.g), 255);
    this->b = std::fmin(std::abs(b + v.b), 255);
    this->a = std::fmin(std::abs(a + v.a), 255);
    this->calculateColor();
    return *this;
}

Color& Color::operator*=(double t) {
    this->r = std::fmin(std::abs(r * t), 255);
    this->g = std::fmin(std::abs(g * t), 255);
    this->b = std::fmin(std::abs(b * t), 255);
    this->a = std::fmin(std::abs(a * t), 255);
    this->calculateColor();
    return *this;
}

Color& Color::operator/=(double t) {
    return *this *= 1/t;
}


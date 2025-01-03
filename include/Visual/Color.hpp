#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <cstdint>
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
    public:
    int r,g,b,a;
    uint32_t original;
    Color(){};

    Color(uint32_t color){
        
        r = (color >> 24) & 0xFF;
        g = (color >> 16) & 0xFF;
        b = (color >> 8) & 0xFF;
        a = color & 0xFF;
        original = color;
    }
    
    Color(int r,int g,int b,int a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        calculateColor();
    }
    
    Color(int r,int g,int b){

        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;

        calculateColor();
    }

    Color Darkened(float p){
        Color res = *this;
        if(p<0)p=0;
        if(p>1)p=1;
        res.r = this->r*p;
        res.g = this->g*p;
        res.b = this->b*p;
        res.calculateColor();
        return res;
    }
    
    Color Shininess(float p){
        Color res = *this;
        if(p<0)p=0;        
        res.r = this->r*p;
        res.g = this->g*p;
        res.b = this->b*p;
        if(res.r > 255)
            res.r = 255;
        if(res.g > 255)
            res.g = 255;
        if(res.b > 255)
            res.b = 255;
        res.calculateColor();
        return res;
    }

    static Color Addition(Color c1, Color c2){
        Color res = Color::Black();
        res.r = c1.r + c2.r;
        res.g = c1.g + c2.g;
        res.b = c1.b + c2.b;
        res.calculateColor();
        return res;
    }

    void calculateColor(){
        original = (r<<24)+(g<<16)+(b<<8)+a;
    }
    void showColor(){
        cout<<"R:"<<r<<",G:"<<g<<",B:"<<b<<",A:"<<a<<endl;
    }

    //      Custom Colors
    static Color Grey(){
        Color res = Color(82,84,84);
        return res;
    }
    static Color Black(){
        Color res = Color(0,0,0);
        return res;
    }
    static Color Purple(){
        Color res = Color(137, 11, 176);
        return res;
    }
    static Color Yellow(){
        Color res = Color(212, 227, 9);
        return res;
    }
    static Color Red(){
        Color res = Color(255, 0, 0);
        return res;
    }
    static Color Blue(){
        Color res = Color(0, 0, 255);
        return res;
    }
    static Color Green(){
        Color res = Color(0, 255, 0);
        return res;
    }
    static Color Orange(){
        Color res = Color(255, 171, 15);
        return res;
    }
    static Color LightGreen(){
        Color res = Color(15, 255, 107);
        return res;
    }
};


#endif
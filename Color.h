//
// Created by filipe on 12/08/18.
//

#ifndef PROJECT_COLOR_H
#define PROJECT_COLOR_H

#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <tuple>

class Color{
private:
    std::tuple<double,double,double> glrgb,rgb,hsl;

    void rgbToGl();
    void glToRgb();
    void glToHsl();
    void hslToGl();
    double hue2rgb(double p, double q, double t);
    void _setGL(double r,double g, double b){
        this->glrgb = std::make_tuple(r,g,b);
    }
    void _setRGB(double r,double g, double b){
        this->rgb = std::make_tuple(r,g,b);
    }
    void _setHSL(double h,double s, double l){
        this->hsl=std::make_tuple(h,s,l);
    }

public:
    void setGl(double r,double g, double b);
    void setRGB(double r,double g, double b);
    void setHSL(double h,double s, double l);
    std::tuple<double,double,double> getGL(){return this->glrgb;}
    std::tuple<double,double,double> getRGB(){return this->rgb;}
    std::tuple<double,double,double> getHSL(){return this->hsl;}
    void _Color(double c0,double c1,double c2 ,bool hsl){
        if(c0>1||c1>1||c2>1){
            if(hsl) this->setHSL(c0,c1,c2);
            else this->setRGB(c0,c1,c2);
        }
        else this->setGl(c0,c1,c2);
    }
    Color(double c0,double c1,double c2 ,bool hsl){
       this->_Color(c0,c1,c2,hsl);
    }
    Color(std::tuple<double,double,double> color, bool hsl){
        this->_Color(std::get<0>(color),std::get<0>(color),std::get<0>(color),hsl);
    }
    Color(){
        this->setGl(0,0,0);
    }
    void translateH(double degree);
    void setHue(double degree);
    void setSat(double percent);
    void setLum(double percent);
    Color clone();
};

Color Color::clone() {
    std::tuple<double,double,double> hsl = this->hsl;
    return {hsl,true};
}

void Color::translateH(double degree) {
    int da =(int) (std::get<0>(this->hsl));
    da = (da+((int) degree))%360;
    this->setHSL(da,std::get<1>(this->hsl),std::get<2>(this->hsl));
}

void Color::setHue(double degree) {
    this->setHSL(((int) degree)%360,std::get<1>(this->hsl),std::get<2>(this->hsl));
}

void Color::setSat(double percent) {
    this->setHSL(std::get<0>(this->hsl),((int)percent)%100,std::get<2>(this->hsl));
}
void Color::setLum(double percent) {
    this->setHSL(std::get<0>(this->hsl),std::get<1>(this->hsl),((int)percent)%100);
}


void Color::setGl(double r, double g, double b) {
    this->glrgb= std::make_tuple (r,g,b);
    this->glToRgb();
    this->glToHsl();
}

void Color::setRGB(double r, double g, double b) {
    this->rgb= std::make_tuple (r,g,b);
    this->rgbToGl();
    this->glToHsl();
}

void Color::setHSL(double h, double s, double l) {
    this->hsl = std::make_tuple (h,s,l);
    this->hslToGl();
    this->glToRgb();
}

void Color::rgbToGl(){
    this->_setGL(std::get<0>(this->rgb)/255,std::get<1>(this->rgb)/255,std::get<2>(this->rgb)/255);
}
void Color::glToRgb(){
    this->_setRGB(std::get<0>(this->glrgb)*255,std::get<0>(this->glrgb)*255,std::get<0>(this->glrgb)*255);
}

double Color::hue2rgb(double p, double q, double t){
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < (1.0/6)) return p + (q - p) * 6 * t;
    if(t < (1.0/2)) return q;
    if(t < (2.0/3)) return p + (q - p) * (2.0/3 - t) * 6;
    return p;
}

void Color::hslToGl() {
        double h = std::get<0>(this->hsl)/360;
        double s = std::get<1>(this->hsl)/100;
        double l = std::get<2>(this->hsl)/100;

        if(s == 0){
            this->glrgb = std::make_tuple (l,l,l);
        }else{
            double q = (l < 0.5) ? (l * (1 + s)) : (l + s - (l * s));
            double p = ((2 * l) - q);
            this->glrgb = std::make_tuple (this->hue2rgb(p, q, h + 1.0/3), this->hue2rgb(p, q, h), this->hue2rgb(p, q, h - 1.0/3));
        }
}
void Color::glToHsl() {
        double r = std::get<0>(this->glrgb);
        double g = std::get<1>(this->glrgb);
        double b = std::get<2>(this->glrgb);
        double maxi (r>g?(r>b?r:b):(g>b?g:b));
        double mini (r<g?(r<b?r:b):(g<b?g:b));
        double h=0,s=0,l=0;
        l = (maxi + mini) / 2;

        if(maxi == mini){
            h=s= 0; // achromatic
        }else{
            double d = maxi - mini;
            s = (l > 0.5) ? (d / (2 - maxi - mini)) : (d / (maxi + mini));
            if(maxi == r) h = (g - b) / d + (g < b ? 6 : 0);
            else if(maxi==g)h = (b - r) / d + 2;
            else if(maxi==b)h = (r - g) / d + 4;
            h /= 6;
        }
        this->_setHSL(h*360,s*100,l*100);
}

#endif //PROJECT_COLOR_H

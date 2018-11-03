//
// Created by filipe on 09/08/18.
//

#ifndef PROJECT_VECTOR_H
#include <math.h>
#include <bits/unique_ptr.h>
#include "Item.h"

#define PROJECT_VECTOR_H

#define VECTOR_AXIS_X 0
#define VECTOR_AXIS_Y 1
#define VECTOR_AXIS_Z 2



using namespace std;

//Helpers

double toRad(double deg){
    return  (M_PI*deg)/180;
}

double toDeg(double rad){
    return  (180*rad)/M_PI;
}

//Classe
class Vector:public Item{
public:
    double x = 0;
    double y = 0;
    double z = 0;
    bool used = false;
    Vector(double x, double y):y(y),x(x){}
    Vector(double x, double y,double z):y(y),x(x),z(z){}
    Vector(){}
    double getTheta();
    double getTheta(int axisReference);
    double getTheta(Vector origin,int axisReference);
    double getTheta(Vector origin);
    double getThetaBetween(Vector origin);
    Vector& rotate(float theta);
    Vector& rotate(float theta,Vector axis);
    Vector& scale(float x,float y);
    Vector& scale(float x,float y,float z);
    Vector& scale(float x);
    double len2();
    double len();
    Vector& scaleMod(double num);
    Vector& normalize();
    Vector& project(Vector other);
    Vector& projectN(Vector other);
    Vector& reflect(Vector axis);
    Vector& reflectN(Vector axis);
    Vector& add(Vector other);
    Vector& sub(Vector other);
    Vector clone();
    std::shared_ptr<Item> clonePtr();
    Vector& rot90();
    Vector& reverse();
    double dot(Vector other);
    Vector& copy(Vector v);
    Vector& cross(Vector other);
  //  static vector<Vector*> gramSmith(vector<Vector*> vectors);
};

double Vector::getTheta(){//Pega valor do menor angulo;
    return this->getTheta(Vector());
}

double Vector::getTheta(int axisReference){//Pega valor do menor angulo, no eixo determinado;
    return this->getTheta(Vector(),axisReference);
}

double Vector::getTheta(Vector origin,int axisReference){//Pega valor do menor angulo no eixo determinado, considerando o vetor origem.
    double x = this->x-origin.x;
    double y = this->y-origin.y;
    double z = this->z-origin.z;

    switch (axisReference){
        case VECTOR_AXIS_X: return atan2(sqrt(y*y+z*z),x);
        case VECTOR_AXIS_Y: return atan2(sqrt(x*x+z*z),y);
        case VECTOR_AXIS_Z: return atan2(sqrt(y*y+x*x),z);
        default:
            return INFINITY;
    }
}

double Vector::getThetaBetween(Vector other){//Pega valor do menor angulo no eixo determinado, considerando o vetor origem.
    auto v1 = this->clone().normalize();
    auto v2 = other.clone().normalize();
    return acos(v2.dot(v1));
}

double Vector::getTheta(Vector origin){//Pega valor do menor angulo, considerando o vetor origem.
    double x = this->x-origin.x;
    double y = this->y-origin.y;
    return atan2(y,x);
}

Vector& Vector::copy(Vector v){
    this->x = v.x;
    this->y = v.y;
    return *this;
}
Vector& Vector::rotate(float theta){//Rotaciona anti-horário em theta em 2d.
    double x_rot = this->x*cos(theta)-this->y*sin(theta);
    double y_rot = this->x*sin(theta)+this->y*cos(theta);
    this->x=x_rot;
    this->y=y_rot;
    return *this;
}

Vector& Vector::rotate(float theta,Vector axis) {//Rotaciona anti-horário em theta, no eixo dado, em 3d;
    double sen = sin(theta), cose = cos(theta), ux = axis.x, uy = axis.y,uz = axis.z;
    double ux2 = ux*ux, uy2 = uy*uy,uz2 = uz*uz, mcos = (1-cose), x = this->x,y = this->y, z=this->z;

    double x_rot= x*(cose+ux2*mcos) + y*(ux*uy*mcos-uz*sen) + z*(ux*uz*mcos+uy*sen);
    double y_rot= x*(ux*uy*mcos+uz*sen) + y*(cose+uy2*mcos) + z*(uz*uy*mcos-ux*sen);
    double z_rot= x*(ux*uz*mcos-uy*sen) + y*(uz*uy*mcos+ux*sen) + z*(cose+uz2*mcos);

    this->x = x_rot;
    this->y = y_rot;
    this->z = z_rot;
    return *this;
}


Vector& Vector::scale(float x){//Escalona (direção não muda. Ele não incrementa o módulo, mas sim as componentes)
    this->scale(x,x,x);
    return *this;
}

Vector& Vector::scale(float x,float y){//Escalona (direção e sentido podem mudar)
    this->scale(x,y,1);
    return *this;
}

Vector& Vector::scale(float x,float y,float z){//Escalona (direção e sentido podem mudar)
    this->x*=x;
    this->y*=y;
    this->z*=z;
    return *this;
}


double Vector::len2(){
    return pow(this->x,2)+pow(this->y,2)+pow(this->z,2);
}

double Vector::len(){//Pega módulo
    return sqrt(this->len2());
}

Vector& Vector::scaleMod(double num){//Mesma direção e sentido mas módulo muda
    double mod = this->len();
    double theta = this->getTheta();
    mod *=num;
    this->x = mod*cos(theta);
    this->y = mod*sin(theta);
    return *this;
}

Vector& Vector::normalize(){
    double mod = this->len();
    this->x/=mod;
    this->y/=mod;
    this->z/=mod;
    return *this;
}

Vector& Vector::project(Vector other){
    double amt = this->dot(other) / other.len2();
    this->x = amt * other.x;
    this->y = amt * other.y;
    this->z = amt * other.z;
    return *this;
}

Vector& Vector::projectN(Vector other){
    double amt = this->dot(other);
    this->x = amt * other.x;
    this->y = amt * other.y;
    this->z = amt * other.z;
    return *this;
}

Vector& Vector::reflect(Vector axis){
    double  x = this->x;
    double  y = this->y;
    double  z = this->z;
    this->project(axis).scale(2);
    this->x -= x;
    this->y -= y;
    this->z -= z;
    return *this;
}

Vector& Vector::reflectN(Vector axis){
    double x = this->x;
    double y = this->y;
    double z = this->z;
    this->projectN(axis).scale(2);
    this->x -= x;
    this->y -= y;
    this->z -= z;
    return *this;
}

Vector& Vector::add(Vector other){
    this->x+=other.x;
    this->y+=other.y;
    this->z+=other.z;
    return *this;
}

Vector& Vector::sub(Vector other){
    this->x-=other.x;
    this->y-=other.y;
    this->z-=other.z;
    return *this;
}

Vector Vector::clone(){
    return Vector(this->x,this->y,this->z);
}

std::shared_ptr<Item> Vector::clonePtr(){
    return std::make_shared<Vector>(this->x,this->y,this->z);
}

Vector& Vector::rot90(){
    double x = this->x;
    this->x = this->y;
    this->y = -x;
    return *this;
}

double Vector::dot(Vector other){
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

Vector& Vector::reverse() {
    this->x= -this->x;
    this->y= -this->y;
    this->z= -this->z;
    return *this;
}

Vector& Vector::cross(Vector other){
    double x = this->y*other.z-this->z*other.y;
    double y = this->z*other.x-this->x*other.z;
    double z = this->x*other.y-this->y*other.x;
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

#endif //PROJECT_VECTOR_H
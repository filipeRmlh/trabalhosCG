//
// Created by filipe on 11/08/18.
//

#ifndef PROJECT_LINESTRIP_H
#define PROJECT_LINESTRIP_H

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Item.h"
#include "Vector.h"
#include "Color.h"
#include "Screen.h"


class LineStrip: public Item {
public:
    Color color;
    virtual void draw();
    void refineCurve();
    virtual void kbdAction(unsigned char key);
    LineStrip(){
        double c1 = random(0,360);
        double c2 = random(0,100);
        double c3 = random(0,100);
        this->color = Color(c1,c2,c3,true);
    }
    virtual std::shared_ptr<Item> clonePtr();
};

std::shared_ptr<Item> LineStrip:: clonePtr(){
    return std::make_shared<LineStrip>();
}

void LineStrip::kbdAction(unsigned char key){
    switch (key){
        case 18:
            this->refineCurve();
            break;
        default:
            break;
    }
}
void LineStrip::refineCurve() {
    auto it1 = this->itens.begin(),
    it2 = this->itens.begin(),
    it3 = this->itens.begin();
    it2++;
    advance(it3,2);


    for(;it3!=this->itens.end(); advance(it1,2),it2++,it3++){

        auto v1 = dynamic_pointer_cast<Vector>(*it1);
        auto v2 = dynamic_pointer_cast<Vector>(*it2);
        auto v3 = dynamic_pointer_cast<Vector>(*it3);
        auto nv = dynamic_pointer_cast<Vector>(v2->clonePtr());
        auto nit = this->itens.insert(it2,nv);
        nv = dynamic_pointer_cast<Vector>(*nit);
        Vector vaux = v1->clone().add(nv->clone().sub(*v1).scaleMod(0.75));
        nv->copy(vaux);
        vaux = v3->clone().add(v2->clone().sub(*v3).scaleMod(0.75));
        v2->copy(vaux);
    }

}

void LineStrip::draw() {
    auto c1 = this->color.getGL();
    glPointSize(4);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor4d(std::get<0>(c1),std::get<1>(c1),std::get<2>(c1),0.5);
    for(const std::shared_ptr<Item> &v :this->itens){
        glVertex2f( (float)(dynamic_pointer_cast<Vector>(v))->x, (float)(dynamic_pointer_cast<Vector>(v))->y);
    }
    glEnd();
}

#endif //PROJECT_LINESTRIP_H

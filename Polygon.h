#include <utility>

//
// Created by filipe on 16/08/18.
//

#ifndef PROJECT_POLYGON_H
#define PROJECT_POLYGON_H

#include "Item.h"
#include "Vector.h"
#include "Color.h"
#include "LineStrip.h"
#include "Screen.h"
#include <GL/glut.h>
#include <GL/gl.h>

class Polygon: public LineStrip {
public:
    list<pair<shared_ptr<Vector>,shared_ptr<Vector>>> arestas;
    Color color1;
    Color color2;
    virtual void draw();
    virtual void kbdAction(unsigned char key);
    Polygon(){
        double c1 = random(0,360);
        double c2 = random(20,100);
        double c3 = random(10,100);
        this->color1 = Color(c1,c2,c3,true);
        this->color2 = this->color1.clone();
        this->color2.translateH(180);
    }
    virtual std::shared_ptr<Item> clonePtr();
    void makeArestas(shared_ptr<Vector> V1,shared_ptr<Vector> V2);
    void marcaConv(shared_ptr<Polygon>conv);
    bool marcaUnion(pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta);
    bool arestaIgual(pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta1,pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta2);
    Vector centroid = Vector();
};
std::shared_ptr<Item>  Polygon:: clonePtr(){
    return make_shared<Polygon>();
}

void Polygon::kbdAction(unsigned char key){
    switch (key){
        case 18:
            break;
        default:
            break;
    }
}

void Polygon::makeArestas(shared_ptr<Vector>V1,shared_ptr<Vector>V2){
    this->arestas.push_back(pair<shared_ptr<Vector>,shared_ptr<Vector>>(V1,V2));
}

bool Polygon::arestaIgual(pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta1,pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta2){
    return ((aresta2.first == aresta1.first) && (aresta1.second == aresta2.second)) || ((aresta1.first == aresta2.second) && (aresta1.second == aresta2.first));
}

bool Polygon::marcaUnion(pair<shared_ptr<Vector>,shared_ptr<Vector>>aresta){
    int count = 0;
    for(auto i : this->arestas){
        auto P = to<Item>(i.second);
        if(find(i.first->nbrs.begin(),i.first->nbrs.end(),P)==i.first->nbrs.end()){
            if(arestaIgual(i,aresta)){
                i.first->nbrs.push_back(i.second);
                i.second->nbrs.push_back(i.first);
            }
        }else{
            count ++;
        }
    }
    return count>=2;
}

void Polygon::marcaConv(shared_ptr<Polygon>conv){
     for(auto i : this->arestas){
         for(auto j : conv->arestas){
             if(this->arestaIgual(i,j)){
                 auto P = to<Item>(i.second);
                 if(find(i.first->nbrs.begin(),i.first->nbrs.end(),P)==i.first->nbrs.end()){
                     i.first->nbrs.push_back(i.second);
                     i.second->nbrs.push_back(i.first);
                 }
             }
         }
     }
}

void Polygon::draw(){
    auto c1 = this->color1.getGL();
    auto c2 = this->color2.getGL();
     glLineWidth(1);
    double cx=0;
    double cy=0;
    int i = 0;
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(this->itens.size()>2) glBegin(GL_POLYGON);

    glColor4d(std::get<0>(c1),std::get<1>(c1),std::get<2>(c1),0.5);
    for(std::shared_ptr<Item> v :this->itens){
        auto vi = dynamic_pointer_cast<Vector>(v);
        cx += vi->x;
        cy += vi->y;
        glVertex2f( (float)vi->x, (float)vi->y);
        i++;
    }
    glEnd();
    glColor4d(std::get<0>(c2),std::get<1>(c2),std::get<2>(c2),1);

    glBegin(GL_LINE_STRIP);
    for(auto aresta :this->arestas){
        auto v1 = aresta.first;
        auto v2 = aresta.second;
        glVertex2f( (float)v1->x, (float)v1->y);
        glVertex2f( (float)v2->x, (float)v2->y);
    }
    glEnd();
//    glEnd();
//    glBegin(GL_LINE_LOOP);
//    for(std::shared_ptr<Item> v :this->itens){
//        auto vi = dynamic_pointer_cast<Vector>(v);
//        glVertex2f( (float)vi->x, (float)vi->y);
//    }
    this->centroid.x = cx/i;
    this->centroid.y = cy/i;
//    glEnd();
}

#endif //PROJECT_POLYGON_H

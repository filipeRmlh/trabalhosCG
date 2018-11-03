#include <utility>

//
// Created by filipe on 18/08/18.
//

#ifndef PROJECT_POINT_H
#define PROJECT_POINT_H

#include <GL/gl.h>
#include <iostream>
#include <memory>
#include "Screen.h"
#include "Polygon.h"
#include "Vector.h"
#include "Item.h"
#include "Color.h"
#include "Edge.h"
#include "HalfEdge.h"

class Point:public Item {
public:
    Color color1;
    Color color2;
    virtual void draw();
    virtual void kbdAction(unsigned char key);
    Point(){
        this->color1 = Color(random(0,360),50,10,true);
        this->color2 = this->color1.clone();
        this->color2.setLum(50);
        this->color2.setSat(60);
    }
    virtual std::shared_ptr<Item> clonePtr();
    void checkInOut(std::shared_ptr<Vector> P);
    bool intersects(Vector p1,Vector p2, Vector p3, Vector p4);
    void jarvis();
    std::shared_ptr<Polygon> jarvis(bool push);
    std::shared_ptr<HalfEdge> delaunay(bool push);
    shared_ptr<Polygon> tridel(shared_ptr<Vector> V1, shared_ptr<Vector> V2);
    void delaunay();
};

std::shared_ptr<Item> Point:: clonePtr(){
    return std::make_shared<Point>();
}

void Point::kbdAction(unsigned char key){
        switch (key){
            case 18:
                break;
            case 10:
                this->jarvis();
                break;
            case 4:
                this->delaunay();
                break;
            default:
                break;
        }
}
void Point::jarvis(){
    this->jarvis(true);
}

std::shared_ptr<Polygon> Point::jarvis(bool push) {
    auto p = std::make_shared<Polygon>();
    //Escolhe ponto mais abaixo.
    auto primeiro = dynamic_pointer_cast<Vector>(this->itens.front());

    for (auto i:this->itens) {
        auto v = dynamic_pointer_cast<Vector>(i);
        primeiro = (v->y < primeiro->y) ? v : primeiro;
    }

    double clockwise = (primeiro->x < 0) ? primeiro->x - 1 : 0;

    auto pant = std::make_shared<Vector>(clockwise, primeiro->y);
    std::shared_ptr<Vector> patual = primeiro;
    std::shared_ptr<Vector> pnext = primeiro;
    std::shared_ptr<Vector> pcand;

    do {
        double dot = -1000;
        Vector v1 = patual->clone().sub(*pant).normalize();
        for (auto item : this->itens) {
            pcand = dynamic_pointer_cast<Vector>(item);
            if (pcand != pnext) {
                Vector v2 = pcand->clone().sub(*patual).normalize();
                double ndot = v2.dot(v1);
                if (ndot > dot) {
                    pnext = pcand;
                    dot = ndot;
                }
            }
        }

        p->makeArestas(patual,pnext);
        p->itens.push_back(patual);
        pant = patual;
        patual = pnext;
    } while (patual != primeiro);

    if (push) {
        auto s = (Screen *) this->screen;
        s->itens.push_back(p);
        s->lastHolded = p;
    }
    return p;
}


shared_ptr<Polygon> Point::tridel(shared_ptr<Vector> V1, shared_ptr<Vector> V2) {

    Vector vr2 = Vector();
    Vector vr3 = Vector();
    Vector vr1 = Vector();
    shared_ptr<Vector> P;

    vr1.copy(*V2).sub(*V1);

    double theta = -INFINITY;
    shared_ptr<Vector> pcand;

    //O for abaixo apenas acha o P;
    for(auto i : this->itens){//Para cada ponto
        pcand = dynamic_pointer_cast<Vector>(i);
        vr2.copy(*pcand).sub(*V1);
        vr3.copy(vr1).cross(vr2);

        if(vr3.z>0){
            vr2.copy(*V1).sub(*pcand);
            vr3.copy(*V2).sub(*pcand);
            double tcand = abs(vr3.getThetaBetween(vr2));
            if(tcand > theta){
                theta = tcand;
                P = pcand;
            }
        }
    }

    auto t = make_shared<Polygon>();
    t->itens.push_back(V1);
    t->itens.push_back(V2);
    t->itens.push_back(P);
    t->makeArestas(V1,V2);
    t->makeArestas(V2,P);
    t->makeArestas(P,V1);
    return t;
}

void Point::delaunay() {
    this->delaunay(true);
}

std::shared_ptr<HalfEdge> Point::delaunay(bool push){
    std::list<std::shared_ptr<Polygon>> f;
    auto he = make_shared<HalfEdge>();
    auto conv = jarvis(false);

    auto it = conv->itens.begin();
    auto V1 = (dynamic_pointer_cast<Vector>(*it));
    it++;
    auto V2 = (dynamic_pointer_cast<Vector>(*it));

    auto t=this->tridel(V1,V2); //Pega primeiro triangulo Delaunay;
    he->itens.push_back(t);
    f.push_front(t);
    t->marcaConv(conv);

    while(!f.empty()){//Para cada triangulo
        t = f.back();
        f.pop_back();

        for(auto aresta : t->arestas){
            bool erro = false;
            auto nb = aresta.first->nbrs;
            if(find(nb.begin(),nb.end(),aresta.second)==nb.end()){
                shared_ptr<Polygon> tlinha = this->tridel(aresta.second,aresta.first);
                f.push_front(tlinha);
                erro = tlinha->marcaUnion(aresta);
                tlinha->marcaConv(conv);
                if(!erro)he->itens.push_back(tlinha);
            }
        }
    }
    if(push){
        auto s = (Screen*) this->screen;
        s->itens.push_back(he);
        s->lastHolded=he;
    }
    return he;
}

bool Point::intersects(Vector p1,Vector p2,Vector p3,Vector p4){
        Vector p1_p2 = p2.clone().sub(p1);
        Vector p1_p3 = p3.clone().sub(p1);
        Vector p1_p4 = p4.clone().sub(p1);
        Vector p3_p1 = p1.clone().sub(p3);
        Vector p3_p2 = p2.clone().sub(p3);
        Vector p3_p4 = p4.clone().sub(p3);
        Vector C1 = p1_p2.clone().cross(p1_p4);
        Vector C2 = p1_p2.clone().cross(p1_p3);
        Vector C3 = p3_p4.clone().cross(p3_p1);
        Vector C4 = p3_p4.clone().cross(p3_p2);
        return (C1.dot(C2)<0)&&(C3.dot(C4)<0);
}

void Point::checkInOut(std::shared_ptr<Vector> P){
        auto c2 = color2.getGL();
        auto s = (Screen*)this->screen;

        for(auto polygon:s->itens){
            if(IsType<Polygon>(*polygon)){
                auto pol = (dynamic_pointer_cast<Polygon>(polygon));

                Vector ref = pol->centroid.sub(Vector(-10000,-10000));
                Vector P_Q = ref.clone().sub(*P);
                int numcross = 0;
                auto it1 = polygon->itens.begin(), it2 = polygon->itens.begin();
                it2++;
                for(;it2!=polygon->itens.end();it1++,it2++){
                        auto PV1 = (dynamic_pointer_cast<Vector>(*it1));
                        auto PV2 = (dynamic_pointer_cast<Vector>(*it2));
                        if(this->intersects(*P,ref,*PV2,*PV1))numcross++;
                }

                auto inicio = dynamic_pointer_cast<Vector>(pol->itens.front());
                auto fim = dynamic_pointer_cast<Vector>(pol->itens.back());

                if(this->intersects(*P,ref,*inicio,*fim))numcross++;
                if(numcross%2){
                    glColor4d(std::get<0>(c2),std::get<1>(c2),std::get<2>(c2),1);
                    break;
                }
            }
        }

}

void Point::draw() {
        auto c1 = this->color1.getGL();
        glPointSize(8.0);
        glBegin(GL_POINTS);
        for(const auto &v :this->itens){
             auto vector = std::dynamic_pointer_cast<Vector>(v);
                glColor4d(std::get<0>(c1),std::get<1>(c1),std::get<2>(c1),1);
                this->checkInOut(vector);
                glVertex2f( (float)vector->x, (float)vector->y);
        }
        glEnd();
}

#endif //PROJECT_POINT_H

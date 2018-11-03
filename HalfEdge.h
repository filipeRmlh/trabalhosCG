//
// Created by filipe on 22/09/18.
//

#ifndef PROJECT_HALFEDGE_H
#define PROJECT_HALFEDGE_H


#include "Item.h"
#include "Polygon.h"

class HalfEdge:public Item {
public:
    void draw() override;
    void kbdAction(unsigned char key) override;
    HalfEdge() = default;

    std::shared_ptr<Item> clonePtr() override;
};

std::shared_ptr<Item> HalfEdge:: clonePtr(){
    return std::make_shared<HalfEdge>();
}

void HalfEdge::kbdAction(unsigned char key){
    switch (key){
        default:
            break;
    }
}

void HalfEdge::draw(){
    for (auto item : this->itens) {
       auto p = dynamic_pointer_cast<Polygon>(item);
       p->draw();
    }
};


#endif //PROJECT_HALFEDGE_H

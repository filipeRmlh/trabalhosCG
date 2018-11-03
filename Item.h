#include <memory>

//
// Created by filipe on 11/08/18.
//

#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H

#include <map>
#include <list>
#include <iostream>
#include <memory>
#include <algorithm>
#include <bits/unique_ptr.h>

using  namespace std;

template <class DstType, class SrcType>
bool IsType(const SrcType& src)
{
    return (typeid(src) == typeid(const DstType));
};

template <class DstType, class SrcType>
std::shared_ptr<DstType> to(const SrcType& src)
{
   return dynamic_pointer_cast<DstType>(src);
};

double random(int min, int max) //range : [min, max)
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) ); //seeding for the first time only!
        //first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

class Item {
protected:
    std::shared_ptr<Item>selfOrigin;
    std::shared_ptr<Item>centerPoint;
public:
    std::list<std::shared_ptr<Item>> nbrs;//Neighbours
    string itemType;
    std::list<std::shared_ptr<Item>> itens;  //Lista de itens que serão desenhados na tela.
    std::shared_ptr<Item> lastDrawing ;
    Item* screen;
    Item(){}
    virtual void draw();
    virtual std::shared_ptr<Item> clonePtr();
    virtual void collide(Item item);
    virtual void collided(Item item);
    virtual void kbdAction(unsigned char key);
    virtual std::_List_iterator<std::shared_ptr<Item>> pIn(std::shared_ptr<Item> p);
    virtual std::_List_iterator<std::shared_ptr<Item>> nIn(std::shared_ptr<Item> p);
};
void Item::kbdAction(unsigned char key) {}
void Item::collide(Item item){}
void Item::collided(Item item){}
void Item::draw(){};

map<string, std::shared_ptr<Item>> classItems;

std::shared_ptr<Item> Item:: clonePtr(){
    return std::make_shared<Item>();
}

void loadItem(string name,std::shared_ptr<Item> item){
    item->itemType=name;
    classItems.insert(std::pair<string,shared_ptr<Item>>(name,(item)));
}

std::_List_iterator<std::shared_ptr<Item>> positionIn(std::shared_ptr<Item> p, std::list<std::shared_ptr<Item>> l){
    for(auto it = l.begin();it!= l.end();it++){
        if((*it)==p) {
            return it;
        }
    }
    return l.end();
}


std::_List_iterator<std::shared_ptr<Item>> Item::pIn(std::shared_ptr<Item> p){
    return positionIn(p,this->itens);
}

std::_List_iterator<std::shared_ptr<Item>> Item::nIn(std::shared_ptr<Item> p){
    return positionIn(p,this->nbrs);
}



#endif


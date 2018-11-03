///*
////
//// Created by filipe on 22/09/18.
////
//
//#ifndef PROJECT_EDGE_H
//#define PROJECT_EDGE_H
//
//
//#include "Item.h"
//#include "Vector.h"
//
//class Edge: public Item{
//public:
//    string id;
//    bool visitado = false;
//    Edge(Vector *v1,Vector* v2){
//        this->itens.push_front(v1);
//        this->itens.push_front(v2);
//        this->id = to_string(v1->x)+"|"+to_string(v1->y)+"/"+ to_string(v2->x)+"|"+to_string(v2->y);
//    }
//    void setId(){
//        auto v1 = this->getV1();
//        auto v2 = this->getV2();
//        this->id = to_string(v1->x)+"|"+to_string(v1->y)+"/"+ to_string(v2->x)+"|"+to_string(v2->y);
//    }
//    Edge(){}
//    void setV1(Vector* v1){
//        if(this->itens.size()==2) this->itens.pop_back();
//        this->itens.push_back(v1);
//        this->setId();
//    }
//    void setV2(Vector* v2){
//        if(this->itens.size()==2) this->itens.pop_front();
//        this->itens.push_back(v2);
//        this->setId();
//    }
//    Vector* getV1(){
//        return (Vector*)this->itens.back();
//    }
//    Vector* getV2(){
//        return (Vector*)this->itens.front();
//    }
//    bool equals(Edge e2);
//};
//bool Edge::equals(Edge e2) {
//    Vector* e2V1 = e2.getV1();
//    Vector* e2V2 = e2.getV2();
//    Vector* eV1 = this->getV1();
//    Vector* eV2 = this->getV2();
//    return ((eV1 == e2V1)&&(eV2 == e2V2))||((eV2 == e2V1)&&(eV1 == e2V2));
//}
//
//#endif //PROJECT_EDGE_H
//*/

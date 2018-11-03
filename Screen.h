#include <utility>

//
// Created by filipe on 09/08/18.
//

#ifndef PROJECT_SCREEN_H
#define PROJECT_SCREEN_H



#include "Vector.h"
#include <GL/gl.h>     // The GL Header File
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <functional>
#include "Item.h"
#include "Color.h"
#include <iostream>
#include <map>

#include <list>

class Screen:public Item{//Esta classe serve para gerenciar a tela correspondente.
private:

    bool menuOpened=false;
    Vector mousePos = Vector(); //Posição do mouse para consulta.
    bool mousePressed = false; //Se algum botão do mouse está pressionado enquanto ele se move;
    std::shared_ptr<Item> holded;

    Color screenColor=Color();
    Vector size; //Vetor que determina tamanho da janela.

public:
    std::shared_ptr<Item> lastHolded;
    string name; //Titulo da Janela.
    Screen(){
        this->name="Window";
        this->size=Vector(400,400);
        this->screenColor.setGl(1,1,1);
    }
    Screen(string name,int w, int h){
        this->name= std::move(name);
        this->screenColor.setGl(0,0,0);
        this->size = Vector(w,h);
        this->window();
    }

    Screen(string name,int w, int h,Color color){
        this->name= std::move(name);
        this->screenColor=color;
        this->size = Vector(w,h);
        this->window();
    }

    std::map<int,string> objectChoices;
    string chosenObject;

    std::list<std::shared_ptr<Item>> itens;  //Lista de itens que serão desenhados na tela.



    void setMenu();

    static void mouseStartAction(int button, int state, int X, int Y);
    static void mouseMoveAction(int X, int Y);
    static void mouseMoveClickedAction(int X, int Y);
    static void displayStartAction();
    static void keyboardStartAction(unsigned char key, int x, int y);
    static void windowResizeAction(int x, int y);
    static void menuStartAction(int value);

    void menuAction(int value);

    void displayAction(){
        std::tuple<double,double,double> color = this->screenColor.getGL();

        glClearColor((float)std::get<0>(color),(float)std::get<1>(color),(float) std::get<2>(color), 0.5);
        glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        for(std::shared_ptr<Item> a:this->itens){
            a->draw();
        }
        glFlush();
        glutSwapBuffers();
        glutPostRedisplay();
    }

    Vector getMousePos(){
        return mousePos;
    }
    bool isMousePressed(){
        return mousePressed;
    }
    void eraseLastItem();
    void mouseClick (int button, int state, int X, int Y);
    void mouseMove (bool pressed, int X, int Y);
    void keyboardAction (unsigned char key, int x, int y);
    void window();
    std::shared_ptr<Item> createObject(string name);
    Vector translatePos(Vector v);
    void resizeScreen(int x,int y);
    void stopDraw();
    void clearScreen();
};

void Screen::stopDraw() {
    this->holded->lastDrawing=nullptr;
    if(!this->holded->itens.empty()){
        this->holded->itens.pop_back();
    }
    this->holded = nullptr;
}

Vector Screen::translatePos(Vector v) {
    return Vector(((2*v.x)/this->size.x)-1, -((2*v.y)/this->size.y)+1);
}

std::map<int,Screen> windows;

void Screen::mouseClick(int button, int state, int x, int y) {
    if(state==GLUT_DOWN){
        if(button == GLUT_LEFT_BUTTON){
            if(!this->menuOpened){
                auto v = make_shared<Vector>();
                v->copy(this->translatePos(Vector(x,y)));

                if(this->holded == nullptr) {
                    auto a = createObject(this->chosenObject);
                    a->itens.push_back(v);
                    this->itens.push_back(a);
                    this->holded = this->itens.back();
                    if(this->holded->itens.size()<=1){
                        auto v2 = make_shared<Vector>();
                        v2->copy(this->translatePos(Vector(x,y)));
                        this->holded->itens.push_back(v2);
                        this->holded->lastDrawing = v2;
                    }
                    this->holded->screen= this;
                }else{
                    this->holded->lastDrawing=v;
                    this->holded->itens.push_back(v);
                }
                this->lastHolded = holded;
            }
        }
    }
}

void Screen::mouseMove(bool pressed, int x, int y) {
    this->mousePressed = pressed;
    Vector pos = translatePos(Vector(x,y));

    this->mousePos.x = pos.x;
    this->mousePos.y = pos.y;

    if(this->holded!= nullptr&&this->holded->lastDrawing!= nullptr){
        (std::dynamic_pointer_cast<Vector>(this->holded->lastDrawing))->x = mousePos.x;
        (std::dynamic_pointer_cast<Vector>(this->holded->lastDrawing))->y = mousePos.y;
    }
}

void Screen::eraseLastItem(){
    if(!this->itens.empty()){
        this->itens.back()->itens.clear();
        this->itens.pop_back();
        this->holded = nullptr;
        if(!this->itens.empty())
            this->lastHolded = this->itens.back();
    }
}

void Screen::clearScreen(){
    if(!this->itens.empty()){
        this->itens.clear();
        this->lastHolded = nullptr;
        this->holded = nullptr;
    }
}

void Screen::keyboardAction (unsigned char key, int x, int y){

    if(glutGetModifiers() != GLUT_ACTIVE_CTRL){
        switch (key){
            case 27: this->stopDraw();
                break;
            case 'c':
                this->eraseLastItem();
                break;
            case 'l':
                this->clearScreen();
                break;
            default:
                break;
        }
    }else if(this->itens.size()>0){
        this->lastHolded->kbdAction(key);
    }
}

std::shared_ptr<Item> Screen::createObject(string name){
    return classItems[name]->clonePtr();
}

void Screen::resizeScreen(int x, int y) {
   this->size.x=x;
   this->size.y=y;
    glutInitWindowSize (x,y);
}

void Screen::menuAction(int value){
    string name = this->objectChoices[value];
    this->chosenObject = name;
}


void Screen::setMenu(){
    glutCreateMenu(Screen::menuStartAction);
    int i=0;
    for (auto it=classItems.begin(); it!=classItems.end(); ++it,i++){
        glutAddMenuEntry(it->first.c_str(),i);
        this->objectChoices.insert(pair<int,string>(i,it->first.c_str()));
    }

    this->chosenObject=this->objectChoices[0];
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void Screen::window() {
    glutInitWindowSize ((int) this->size.x,(int) this->size.y);
    glutCreateWindow(this->name.c_str());
    glutMouseFunc(Screen::mouseStartAction);
    glutMotionFunc(Screen::mouseMoveAction);
    glutPassiveMotionFunc(Screen::mouseMoveClickedAction);
    glutKeyboardFunc(Screen::keyboardStartAction);
    glutDisplayFunc(Screen::displayStartAction);

    this->setMenu();

    glutReshapeFunc(Screen::windowResizeAction);
    windows.insert(std::pair<int,Screen>(glutGetWindow(),*this));
}


void Screen::menuStartAction(int value){
    windows[glutGetWindow()].menuAction(value);
}

void Screen::mouseStartAction(int button, int state, int X, int Y) {
    windows[glutGetWindow()].mouseClick(button,state,X,Y);
}

void Screen::mouseMoveAction(int X, int Y) {
    windows[glutGetWindow()].mouseMove(false,X,Y);
}

void Screen::mouseMoveClickedAction(int X, int Y) {
    windows[glutGetWindow()].mouseMove(true,X,Y);
}

void Screen::displayStartAction() {
    windows[glutGetWindow()].displayAction();
}

void Screen::keyboardStartAction(unsigned char key, int x, int y) {
    windows[glutGetWindow()].keyboardAction(key,x,y);
}

void Screen::windowResizeAction(int x, int y) {
    windows[glutGetWindow()].resizeScreen(x,y);
}
#endif //PROJECT_SCREEN_H



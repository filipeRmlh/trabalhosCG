#include <memory>

#include <memory>

/*
 When creating your project, uncheck OWL,
 uncheck Class Library, select Static
 instead of Dynamic and change the target
 model to Console from GUI.
 Also link glut.lib to your project once its done.
 */

#include <stdlib.h>
#include<string>
#include<iostream>
//
//// change OpenGL to GL
#include <GL/gl.h>     // The GL Header File
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <iostream>
#include <memory>
#include <math.h>
#include <random>
#include "Vector.h"
#include "Screen.h"
#include "Color.h"
#include "LineStrip.h"
#include "Polygon.h"
#include "Point.h"

using namespace std;

void loadItems(){
    loadItem("LineStrip", std::make_shared<LineStrip>());
    loadItem("Polygon", std::make_shared<Polygon>());
    loadItem("Point", std::make_shared<Point>());
}

int main(int argc, char **argv){
    loadItems();
    glutInit(&argc,argv);
    Screen s = Screen("Trabalho4",500,500);
    glutMainLoop();
    return EXIT_SUCCESS ;
}
//
//  main.cpp
//  OpenGl-01-HelloWorld
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

void draw() {
    //set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //set coldr read
    glColor3f(1.0f, 0.0f, 0.0f);
    //set draw coordinate
    //maybe some bug for this.
//    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
    //begin render
    glBegin(GL_POLYGON);
    //set 4 point of top for polygon
    glVertex3f(0.25f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.75f, 0.0f);
    glVertex3f(0.25f, 0.75f, 0.0f);
    //end render
    glEnd();
    //fouse refush buffer,
    glFlush();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    // init GLUT Lib
    glutInit(&argc, (char**)argv);
    //create a window and name it
    glutCreateWindow("HelloWorld");
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

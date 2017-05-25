//
//  main.m
//  tempMac
//
//  Created by Mark Ran on 2017/5/23.
//  Copyright © 2017年 markran. All rights reserved.
//

//#import <Cocoa/Cocoa.h>
//
//int main(int argc, const char * argv[]) {
//    return NSApplicationMain(argc, argv);
//}

//http://blog.csdn.net/sarkuya/article/details/5819743#

#include <GLUT/GLUT.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.4, 0.4);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Xcode Glut Demo");
    glutDisplayFunc(display);
    glutMainLoop();
}

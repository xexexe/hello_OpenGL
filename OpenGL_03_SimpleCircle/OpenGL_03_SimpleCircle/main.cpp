//
//  main.cpp
//  OpenGL_03_SimpleCircle
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

#define PI 3.1415926

/**
 *  初始化操作
 */
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //设置着色模式，GL_FLAT 采用恒定着色，使用图元中某个顶点的颜色来渲染整个图元。
    glShadeModel(GL_FLAT);
}

/**
 *  绘制一条直线
 *
 *  @param x1 x1
 *  @param y1 x2
 *  @param x2 y1
 *  @param y2 y2
 */
void drawOneLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

/**
 *  展示绘制效果
 */
void display() {
    //清理颜色缓冲区
    
    int i;
    
    glClear (GL_COLOR_BUFFER_BIT);
    
    /* select white for all lines  */
    glColor3f (1.0, 0.0, 0.0);
    
    /* in 1st row, 3 lines, each with a different stipple  */
    //开启直线的点画功能
    glEnable (GL_LINE_STIPPLE);
    //设置直线的点画模式
    glLineStipple (1, 0x0101);  /*  dotted  */
    //绘制一条直线
    drawOneLine (50.0, 125.0, 150.0, 125.0);
    glLineStipple (1, 0x00FF);  /*  dashed  */
    drawOneLine (150.0, 125.0, 250.0, 125.0);
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (250.0, 125.0, 350.0, 125.0);
    
    /* in 2nd row, 3 wide lines, each with different stipple */
    glLineWidth (5.0);
    glLineStipple (1, 0x0101);  /*  dotted  */
    drawOneLine (50.0, 100.0, 150.0, 100.0);
    glLineStipple (1, 0x00FF);  /*  dashed  */
    drawOneLine (150.0, 100.0, 250.0, 100.0);
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (250.0, 100.0, 350.0, 100.0);
    glLineWidth (1.0);
    
    /* in 3rd row, 6 lines, with dash/dot/dash stipple  */
    /* as part of a single connected line strip         */
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    glBegin (GL_LINE_STRIP);
    for (i = 0; i < 7; i++)
        glVertex2f (50.0 + ((GLfloat) i * 50.0), 75.0);
    glEnd ();
    
    /* in 4th row, 6 independent lines with same stipple  */
    for (i = 0; i < 6; i++) {
        drawOneLine (50.0 + ((GLfloat) i * 50.0), 50.0,
                     50.0 + ((GLfloat)(i+1) * 50.0), 50.0);
    }
    
    /* in 5th row, 1 line, with dash/dot/dash stipple    */
    /* and a stipple repeat factor of 5                  */
    glLineStipple (5, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (50.0, 25.0, 350.0, 25.0);
    
    //关闭直线的点画功能
    glDisable (GL_LINE_STIPPLE);
    glFlush ();
}

/**
 *  调整窗口尺寸
 *
 *  @param width  宽度
 *  @param height 高度
 */
void reshape(int width, int height) {
    //设置视口矩形区域，在默认情况下，视口被设置为占据打开窗口的整个像素矩形
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //对投影矩阵应用随后的矩阵操作
    glMatrixMode(GL_PROJECTION);
    //等于是将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵！等于是之前的矩阵变换带来的影响到此为止了！
    glLoadIdentity();
    //指定2D裁剪坐标系，naer和far使用默认值-1和1
    gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
}

/**
 *  键盘事件回调
 *
 *  @param key 键位
 *  @param x   宽度
 *  @param y   高度
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //初始化GLUT库
    glutInit(&argc, (char**)argv);
    //设置双缓冲，RGB像素格式的窗口
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //设置窗口大小
    glutInitWindowSize(400, 150);
    //设置窗口坐标
    glutInitWindowPosition (100, 100);
    //创建窗口
    glutCreateWindow("Lines");
    
    //初始化操作
    init();
    
    //设置展示的回调方法
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    //绘制线程开始循环
    glutMainLoop();
    
    return 0;
}

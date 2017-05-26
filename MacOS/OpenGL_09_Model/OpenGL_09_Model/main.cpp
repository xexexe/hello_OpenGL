//
//  main.cpp
//  OpenGL_09_Model
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

//http://blog.csdn.net/oktears/article/details/42915159

#include <iostream>

#include <GLUT/GLUT.h>

/**
 *  初始化操作
 */
void init() {
    //设置清屏色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //设置着色模式，填充色与顶点一致
    glShadeModel(GL_FLAT);
}

/**
 *  绘制三角形
 */
void draw_triangle() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 25.0);
    glVertex2f(25.0, -25.0);
    glVertex2f(-25.0, -25.0);
    glEnd();
}

/**
 *  展示绘制效果
 */
void display() {
    
    //清理颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    //设置绘制颜色
    glColor3f(1.0, 1.0, 1.0);
    
    
    //1.使用实线绘制三角形
    
    //加载单位矩阵，隔离各个模型的变换效果
    glLoadIdentity();
    //设置绘制颜色
    glColor3f(1.0, 1.0, 1.0);
    //绘制三角形
    draw_triangle();
    
    //2.使用点画虚线绘制三角形，进行平移模型变换
    
    //开启点画线功能
    glEnable(GL_LINE_STIPPLE);
    //设置点画模式，使用短虚线
    glLineStipple(1, 0xF0F0);
    //加载单位矩阵
    glLoadIdentity();
    //沿x轴负方向平移20像素
    glTranslatef(-20.0, 0.0, 0.0);
    //绘制三角形
    draw_triangle();
    
    //3.使用点画虚线绘制三角形，进行缩放模型变换
    
    //设置点画模式，使用长虚线
    glLineStipple(1, 0xF00F);
    //加载单位矩阵
    glLoadIdentity();
    //设置缩放，X轴方向放大1.5倍，Y轴方向所辖0.5倍
    glScalef(1.5, 0.5, 1.0);
    //绘制三角形
    draw_triangle();
    
    //4.使用点画虚线绘制三角形，进行缩放模型变换
    
    //设置点画模式，使用长虚线
    glLineStipple(1, 0x8888);
    //加载单位矩阵
    glLoadIdentity();
    //设置旋转，沿Z轴顺时针旋转90度
    glRotatef(90.0, 0.0, 0.0, 1.0);
    //绘制三角形
    draw_triangle();
    
    //关闭点画线功能
    glDisable(GL_LINE_STIPPLE);
    
    //强制完成绘制指令
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
    //之后的矩阵操作定义为投影矩阵操作
    glMatrixMode(GL_PROJECTION);
    //等于是将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵！等于是之前的矩阵变换带来的影响到此为止了！
    glLoadIdentity();
    
    //它创建一个平行视景体，实际上这个函数的操作是创建一个正射投影矩阵，并且用这个矩阵乘以当前矩阵
    if (width <= height)
        glOrtho(-50.0, 50.0, -50.0 * (GLfloat)height / (GLfloat)width,
                50.0 * (GLfloat)height / (GLfloat)width, -1.0, 1.0);
    else
        glOrtho(-50.0 * (GLfloat)width / (GLfloat)height,
                50.0 * (GLfloat)width / (GLfloat)height, -50.0, 50.0, -1.0, 1.0);
    //之后的矩阵操作定义为模型视图矩阵操作
    glMatrixMode(GL_MODELVIEW);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //初始化GLUT库
    glutInit(&argc, (char**)argv);
    //设置单缓冲，RGB像素格式的窗口
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //设置窗口大小
    glutInitWindowSize(500, 500);
    //设置窗口坐标
    glutInitWindowPosition (100, 100);
    //创建窗口
    glutCreateWindow("Model");
    
    //初始化操作
    init();
    
    //设置展示的回调方法
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    //绘制线程开始循环
    glutMainLoop();
    
    return 0;
}

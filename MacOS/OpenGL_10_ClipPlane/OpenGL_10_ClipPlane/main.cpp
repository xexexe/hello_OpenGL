//
//  main.cpp
//  OpenGL_10_ClipPlane
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

//http://blog.csdn.net/oktears/article/details/42915623

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
 *  展示绘制效果
 */
void display() {
    
    //清理颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    //设置绘制颜色
    glColor3f(1.0, 1.0, 1.0);
    //复制当前矩阵并保存到栈顶
    glPushMatrix();
    //沿z轴负方向移动5个单位长度
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    //定义裁剪平面数组, Ax + By + Cz + D = 0
    GLdouble equn[4] = {0.0f, 1.0f, 0.0f, 0.0f};
    GLdouble equn2[4] = {1.0f, 0.0f, 0.0f, 0.0f};
    
    //设置裁剪平面，y>0
    glClipPlane(GL_CLIP_PLANE0, equn);
    glEnable(GL_CLIP_PLANE0);
    
    //设置裁剪平面，x>0
    glClipPlane(GL_CLIP_PLANE1, equn2);
    glEnable(GL_CLIP_PLANE1);
    
    //沿x轴旋转90度
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    //渲染一个球体，球体半径，以Z轴上线段为直径分布的圆周线的条数(经线)，围绕在Z轴周围的线的条数(维线)
    glutWireSphere(2.0f, 20.0f, 16.0f);
    
    //弹出栈顶矩阵
    glPopMatrix();
    
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
    
    //创建一个表示对称透视视图平截头体的矩阵
    //设置眼睛睁开的角度，视景体的宽高比，近截面的距离，远截面的距离
    gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f);
    
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
    glutCreateWindow("ClipPlane");
    
    //初始化操作
    init();
    
    //设置展示的回调方法
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    //绘制线程开始循环
    glutMainLoop();
    
    return 0;
}

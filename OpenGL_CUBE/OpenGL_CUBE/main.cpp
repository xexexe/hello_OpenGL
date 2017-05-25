//
//  main.cpp
//  OpenGL_CUBE
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

//http://blog.csdn.net/oktears/article/details/42582855

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
    glColor3f (1.0, 1.0, 1.0);
    //加载单位矩阵
    glLoadIdentity();
    //进行视图变换，参数分别为摄像机位置(0.0, 0.0, 5.0)，摄像机朝向(0.0, 0.0, 0.0)朝向原点，朝上的方向向量(0.0, 1.0, 0.0)
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //进行模型变换，变换之后就生成了模型视图矩阵
    glScalef (1.0, 2.0, 1.0);
    //绘制立方体
    glutWireCube(1.0);
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
    //之后的矩阵操作定义为透视矩阵操作
    glMatrixMode(GL_PROJECTION);
    //等于是将之前矩阵变换导致变化过的栈顶矩阵重新归位，置为单位矩阵！等于是之前的矩阵变换带来的影响到此为止了！
    glLoadIdentity();
    //将当前矩阵与一个透视矩阵相乘，把当前矩阵转换为透视矩阵
    //即定义了一个平截头体(视景体)，在视景体内部的模型将被显示，之外的将被裁减
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
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
    glutInitWindowSize(300, 300);
    //设置窗口坐标
    glutInitWindowPosition (100, 100);
    //创建窗口
    glutCreateWindow("CUBE");
    
    //初始化操作
    init();
    
    //设置展示的回调方法
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    //绘制线程开始循环
    glutMainLoop();
    
    return 0;
}

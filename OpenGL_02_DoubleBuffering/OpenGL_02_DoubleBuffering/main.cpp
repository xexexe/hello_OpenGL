//
//  main.cpp
//  OpenGL_02_DoubleBuffering
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

#include <iostream>
//GLUT库，提供一套兼容各种操作系统的OpenGL的图形UI接口
#include <GLUT/GLUT.h>

static GLfloat spin = 0.0f;

/**
 * 初始化操作
 */
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //设置着色模式，GL_FLAT 采用恒定着色，使用图元中某个顶点的颜色来渲染整个图元。
    glShadeModel(GL_FLAT);
}

/**
 *  展示绘制效果
 */
void display() {
    //清理颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    //将当前矩阵压入栈中保存
    glPushMatrix();
    //设置颜色
    glColor3f(1.0f, 0.0f, 0.0f);
    //旋转操作，绕z轴旋转spin度
    glRotatef(spin, 0.0f, 0.0f, 1.0f);
    //构造一个矩形
    glRectf(-25.0f, -25.0f, 25.0f, 25.0f);
    //还原绘制变换前的矩阵
    glPopMatrix();
    //交换缓冲区，将正在显示的颜色缓冲区和正在绘制的颜色缓冲区数据交换
    glutSwapBuffers();
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
    //设置裁剪坐标系
    glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
    //对模型视图矩阵应用随后的矩阵操作
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 *  播放旋转动画
 */
void spinDisplay() {
    spin += 3.0f;
    if (spin > 360.0f) {
        spin -= 360.0f;
    }
    
    //标记当前窗口需要重新绘制。通过glutMainLoop下一次循环时，窗口显示将被回调以重新显示窗口的正常面板。多次调用glutPostRedisplay，在下一个显示回调只产生单一的重新显示回调。
    glutPostRedisplay();
}

/**
 *  鼠标事件回调
 *
 *  @param button 按钮
 *  @param state  状态
 *  @param x      x
 *  @param y      y
 */
void mouse(int button, int state, int x, int y) {
    switch (button) {
            //按下鼠标左键
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                //设置全局的回调函数，当没有窗口事件到达时，GLUT程序功能可以执行后台处理任务或连续动画。如果启用，这个idle function会被不断调用，直到有窗口事件发生。
                //播放旋转动画
                glutIdleFunc(spinDisplay);
            }
            break;
            //按下鼠标右键
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                //停止函数的回调
                //停止旋转动画
                glutIdleFunc(nullptr);
            }
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //初始化GLUT库
    glutInit(&argc, (char**)argv);
    //设置双缓冲，RGB像素格式的窗口
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //设置窗口大小
    glutInitWindowSize(250, 250);
    //创建窗口
    glutCreateWindow("Double Buffer");
    
    //初始化操作
    init();
    
    //设置展示的回调方法
    glutDisplayFunc(display);
    //设置窗口改变时的回调方法
//    glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);
    glutReshapeFunc(reshape);
    //设置鼠标事件回调方法
    glutMouseFunc(mouse);
    //绘制线程开始循环
    glutMainLoop();
    
    return 0;
}

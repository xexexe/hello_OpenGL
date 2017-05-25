//
//  main.cpp
//  OpenGL_11_Planet
//
//  Created by Mark Ran on 2017/5/25.
//  Copyright © 2017年 markran. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

static int year = 0, day = 0;

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
    
    //渲染一个太阳，半径1.0f
    glutWireSphere(1.0f, 20.0f, 16.0f);
    
    //绕y轴旋转year度，此时地球的局部坐标系统与全局坐标系统不一致，表现出公转
    glRotatef((GLfloat)year, 0.0f, 1.0f, 0.0f);
    //沿x轴方向移动2个单位长度，此时地球的局部坐标系统已经与全局的坐标系统偏移
    glTranslatef(2.0f, 0.0f, 0.0f);
    //沿y轴旋转day度，此时地球的局部坐标系统与全局坐标系统一致，表现出自转
    glRotatef((GLfloat)day, 0.0f, 1.0f, 0.0f);
    
    //绘制一个地球，半径0.2f
    glutWireSphere(0.2f, 10.0f, 8.0f);
    
    //弹出栈顶矩阵
    glPopMatrix();
    
    //交换缓冲区数据
    glutSwapBuffers();
    
    //强制完成绘制指令
    //    glFlush();
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
    glLoadIdentity();
    //相机位置(0, 0, 5)，相机镜头朝向(0, 0, 0)，相机顶部朝上
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //如果并没有调用gluLookAt(),那么照相机就被设置为默认的位置和方向。在默认情况下，照相机位于原点，指向z轴的负方向，朝上向量为(0,1,0)。
    
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
        case int('d'):
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case int('D'):
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case int('y'):
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case int('Y'):
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        default:
            break;
            
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //初始化GLUT库
    glutInit(&argc, (char**)argv);
    //设置单缓冲，RGB像素格式的窗口
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //设置窗口大小
    glutInitWindowSize(500, 500);
    //设置窗口坐标
    glutInitWindowPosition (100, 100);
    //创建窗口
    glutCreateWindow("行星系统");
    
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

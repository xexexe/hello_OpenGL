//
//  ViewController.m
//  HelloWorld02
//
//  Created by Mark Ran on 2017/6/28.
//  Copyright © 2017年 markran. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

@interface ViewController () <GLKViewDelegate> {
    EAGLContext *context;
    GLuint vertexID;
    GLuint program;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!context) {
        NSLog(@"Failure to create EA context.");
    }
    
    GLKVector3 vec[3]={
        {0.5,0.5,0.5},
        {-0.5,-0.5,0.5},
        {0.5,-0.5,-0.5}
    };
    
    GLKView *glView = (GLKView *)self.view;
    glView.context = context;
    glView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:context];
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.5, 0.2, 0.1, 1);
    
    [self loadShaders];
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8, 0.2, 0.3, 1);
    glGenVertexArrays(1, &vertexID);    // 生成一个vao对象
    glBindVertexArray(vertexID);        // 绑定vao
    GLuint bufferID;
    glGenBuffers(1, &bufferID);         // 生成vbo
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);                                //绑定
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec), vec, GL_STATIC_DRAW);        //填充缓冲对象
    GLuint loc = glGetAttribLocation(program, "position");                  //获得shaderposition变量的索引
    glEnableVertexAttribArray(loc);                                         //启动这个索引
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLKVector3), 0);   //设置这个索引需要填充的内容
    glBindVertexArray(0);                                                       //释放vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                           //释放vbo
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
#pragma mark - shader

- (BOOL)loadShaders {
    GLuint vertShader = 0, fragShader = 0;
    NSString *vertShaderPathname, *fragShaderPathname;
    
    // Create shader program.
    program = glCreateProgram();
    
    // Create and compile vertex shader.
    vertShaderPathname = [[NSBundle mainBundle] pathForResource:@"shader" ofType:@"vsh"];
    // compile
    if (![self compileShader:&vertShader type:GL_VERTEX_SHADER file:vertShaderPathname]) {
        NSLog(@"Failed to compile vertex shader");
        return NO;
    }
    
    // Create and compile fragment shader.
    fragShaderPathname = [[NSBundle mainBundle] pathForResource:@"shader" ofType:@"fsh"];
    // compile
    if (![self compileShader:&fragShader type:GL_FRAGMENT_SHADER file:fragShaderPathname]) {
        NSLog(@"Failed to compile frag shader");
        return NO;
    }
    
    // Attach vertex shader to program
    glAttachShader(program, vertShader);
    
    // Attach fragment shader to program
    glAttachShader(program, fragShader);
    
    // Link program. todo
    if (![self linkProgram:program]) {
        NSLog(@"Failed to link program: %d", program);
        
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader) {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (program) {
            glDeleteProgram(program);
            program = 0;
        }
        
        return NO;
    }
    
    // Release vertex and fragment shaders.
    if (vertShader) {
        glDetachShader(program, vertShader);
        glDeleteShader(vertShader);
    }
    
    if (fragShader) {
        glDetachShader(program, fragShader);
        glDeleteShader(fragShader);
    }
    
    return YES;
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file {
    GLint status;
    const GLchar *source;
    source = (GLchar *)[[NSString stringWithContentsOfFile:file encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        NSLog(@"Failed to load vertex shader");
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log: \n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    
    return YES;
}

- (BOOL)linkProgram:(GLuint)prog {
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    
    return YES;
}

- (BOOL)validateProgram:(GLuint)prog {
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return NO;
    }
    return YES;
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓冲和深度缓冲
    glBindVertexArray(vertexID);
    glUseProgram(program);                  //使用shader
    glDrawArrays(GL_TRIANGLES, 0, 3);       //绘制三角形
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
}

@end

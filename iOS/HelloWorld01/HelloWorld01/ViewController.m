//
//  ViewController.m
//  HelloWorld01
//
//  Created by Mark Ran on 2017/6/28.
//  Copyright © 2017年 markran. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () <GLKViewDelegate>
{
    EAGLContext *context;
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
    
    GLKView *glView = (GLKView *)self.view;
    glView.context = context;
    glView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:context];
    glEnable(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4, 0.1, 0.2, 1.0);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

@end

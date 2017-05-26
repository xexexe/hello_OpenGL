//
//  AppDelegate.h
//  HelloWorld
//
//  Created by Mark Ran on 2017/5/26.
//  Copyright © 2017年 markran. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end


//
//  HelloWorld01Tests.m
//  HelloWorld01Tests
//
//  Created by Mark Ran on 2017/6/28.
//  Copyright © 2017年 markran. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface HelloWorld01Tests : XCTestCase

@end

@implementation HelloWorld01Tests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end

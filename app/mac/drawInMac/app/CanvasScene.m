//
//  canvasScene.m
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import "CanvasScene.h"
#import "CanvasView.h"
#import "../adaptor/CoreAdaptor.h"


@implementation CanvasScene{
    CanvasView  *canvas;
}

- (void)initView
{
    canvas = [[CanvasView alloc] initWithFrame:CGRectMake(0, 0, self.size.width, self.size.height)];
    [canvas initView];
}

- (void)didMoveToView:(SKView *)view {
    // Setup your scene here
    
    if(!canvas){
    	canvas = [[CanvasView alloc] initWithFrame:CGRectMake(0, 0, self.size.width, self.size.height)];
	}

    [self.view addSubview:canvas];
}


- (void)touchDownAtPoint:(CGPoint)pos {
    [canvas touchDownByPoint:pos];
}

- (void)touchMovedToPoint:(CGPoint)pos {
    [canvas touchMoveByPoint:pos];
}

- (void)touchUpAtPoint:(CGPoint)pos {
    [canvas touchUpByPoint:pos];
}



- (void)mouseDown:(NSEvent *)theEvent {
    CGPoint pos = [theEvent locationInWindow];
    [self touchDownAtPoint: pos];
    [[CoreAdaptor sharedCoreAdaptor] moveTo:pos.x y:pos.y];
}
- (void)mouseDragged:(NSEvent *)theEvent {
    CGPoint pos = [theEvent locationInWindow];
    [self touchMovedToPoint:pos];
    [[CoreAdaptor sharedCoreAdaptor] lineTo:pos.x y:pos.y];
}
- (void)mouseUp:(NSEvent *)theEvent {
    CGPoint pos = [theEvent locationInWindow];
    [self touchUpAtPoint:pos];
    [[CoreAdaptor sharedCoreAdaptor] lineTo:pos.x y:pos.y];
}

- (void)setName:(NSString*)myName dstName:(NSString*)name
{
    [canvas setName:myName dstName:name];
}

- (void)syncMoveToPoint:(CGPoint)pos{
    [canvas syncMoveToPoint:pos];
}

- (void)syncLineToPoint:(CGPoint)pos{
    [canvas syncLineToPoint:pos];
}

-(void)update:(CFTimeInterval)currentTime {
    // Called before each frame is rendered
}

@end

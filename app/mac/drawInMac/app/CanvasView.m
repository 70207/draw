//
//  canvasView.m
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import "CanvasView.h"

@implementation CanvasView{
    CGMutablePathRef    _path_my;
    CGMutablePathRef    _path_dst;
 

}



- (void)initView
{
    _myColor = [NSColor redColor];
    _dstColor = [NSColor greenColor];
}

- (void)setName:(NSString*)myName dstName:(NSString*)name
{
    NSComparisonResult  result = [myName compare:name];
    if(result == NSOrderedAscending){
        _myColor = [NSColor redColor];
        _dstColor = [NSColor greenColor];
    }
    else{
      
        _myColor = [NSColor greenColor];
        _dstColor = [NSColor redColor];
    }
}

- (void)viewDidMoveToWindow{
    [super viewDidMoveToWindow];
    _path_my = CGPathCreateMutable();
    _path_dst = CGPathCreateMutable();

  
}

- (void)touchDownByPoint:(CGPoint)pos
{
    CGPathMoveToPoint(_path_my, 0, pos.x, pos.y);
}

- (void)touchUpByPoint:(CGPoint)pos
{
    CGPathAddLineToPoint(_path_my, 0, pos.x, pos.y);
    
    [self setNeedsDisplay:YES];
}

- (void)touchMoveByPoint:(CGPoint)pos
{
	CGPathAddLineToPoint(_path_my, 0, pos.x, pos.y);
    [self setNeedsDisplay:YES];
}

- (void)syncMoveToPoint:(CGPoint)pos
{
    CGPathMoveToPoint(_path_dst, 0, pos.x, pos.y);
}

- (void)syncLineToPoint:(CGPoint)pos
{
    CGPathAddLineToPoint(_path_dst, 0, pos.x, pos.y);
    [self setNeedsDisplay:YES];
}



- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
    NSGraphicsContext* cc = [NSGraphicsContext currentContext];
    CGContextRef myContext = [cc CGContext];
    
    
    [_myColor set];
    CGContextAddPath(myContext, _path_my);
    CGContextDrawPath(myContext, kCGPathStroke);
    
    
    
    [_dstColor set];
    CGContextAddPath(myContext, _path_dst);
    CGContextDrawPath(myContext, kCGPathStroke);
}

@end

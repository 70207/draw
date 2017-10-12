//
//  canvasView.h
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CanvasView : NSView



@property (nonatomic) NSColor*                myColor;
@property (nonatomic) NSColor*                dstColor;

- (void)initView;
- (void)setName:(NSString*)myName dstName:(NSString*)name;
- (void)touchDownByPoint:(CGPoint)pos;
- (void)touchUpByPoint:(CGPoint)pos;
- (void)touchMoveByPoint:(CGPoint)pos;

- (void)syncMoveToPoint:(CGPoint)pos;
- (void)syncLineToPoint:(CGPoint)pos;


@end

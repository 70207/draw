//
//  canvasScene.h
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

@interface CanvasScene : SKScene

- (void)initView;
- (void)setName:(NSString*)myName dstName:(NSString*)name;
- (void)syncMoveToPoint:(CGPoint)pos;
- (void)syncLineToPoint:(CGPoint)pos;


@end

//
//  coreDelegate.hpp
//  drawInMac
//
//  Created by peter chen on 2017/10/11.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol CoreDelegate <NSObject>
@optional

-(int)onInit:(int)myIp myPort:(int)port;
-(void)onLink:(int)srcIndex srcIp:(int)ip srcPort:(int)port srcName:(const char*)name nameSize:(int)size;
-(void)onConfirm:(int)srcIndex srcName:(const char*)name nameSize:(int)size;
-(void)onCancel:(int)srcIndex;
-(void)onRecvPosMoveTo:(double)x  y:(double)y;
-(void)onRecvPosLineTo:(double)x  y:(double)y;
@end



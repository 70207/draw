//
//  CoreAdaptor.hpp
//  drawInMac
//
//  Created by peter chen on 2017/10/11.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import  "CoreDelegate.h"
#include "CoreUtil.h"

@interface CoreAdaptor : NSObject
single_interface(CoreAdaptor)

@property(nonatomic, weak) id<CoreDelegate>  delegate;


-(void)coreInit;
-(void)link:(const char*)myName nameSize:(int)size  dstIp:(int)ip dstPort:(int)port;
-(void)confirm:(const char*)myName nameSize:(int)size  dstIndex:(int)index;
-(void)cancel:(int)dstIndex;
-(void)sendMsg:(int)dstIndex msg:(const char*)msg size:(int)size;
-(void)moveTo:(double)x y:(double)y;
-(void)lineTo:(double)x y:(double)y;


-(int)onInit:(int)myIp myPort:(int)port;
-(int)onLink:(int)srcIndex srcIp:(int)ip srcPort:(int)port srcName:(const char*)name nameSize:(int)size;
-(int)onConfirm:(int)srcIndex srcName:(const char*)name nameSize:(int)size;
-(int)onCancel:(int)srcIndex;
-(int)onMsg:(int)srcIndex msg:(const char*)msg  size:(int)size;

@end

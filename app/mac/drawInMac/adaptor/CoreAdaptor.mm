//
//  CoreAdaptor.cpp
//  drawInMac
//
//  Created by peter chen on 2017/10/11.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <string.h>
#include "CoreAdaptor.h"
#include "Core.h"
#include "CoreData.h"




@implementation CoreAdaptor{
    Core 	*_core;
    int      _dstIndex;
}
single_implementation(CoreAdaptor)


-(void)coreInit
{
    _core = new Core;
    _core->init();
    _dstIndex = 0;
}





-(void)link:(const char*)myName nameSize:(int)size  dstIp:(int)ip dstPort:(int)port
{
    _core->link(myName, size, ip, port);
}

-(void)confirm:(const char*)myName nameSize:(int)size  dstIndex:(int)index
{
    _core->confirm(myName, size, index);
    _dstIndex = index;
}

-(void)cancel:(int)dstIndex
{
    _core->cancel(dstIndex);
}

-(void)sendMsg:(int)dstIndex msg:(const char*)msg size:(int)size
{
    _core->sendMsg(dstIndex, msg, size);
}

-(void)moveTo:(double)x y:(double)y
{
    struct CoreDataPos  pos;
    pos.header.cmd = CORE_DATA_CMD_POS_MOVE_TO;
    pos.x = x;
    pos.y = y;
    
    _core->sendMsg(_dstIndex, (const char*)&pos, (int)sizeof(pos));
}

-(void)lineTo:(double)x y:(double)y
{
    struct CoreDataPos  pos;
    pos.header.cmd = CORE_DATA_CMD_POS_LINE_TO;
    pos.x = x;
    pos.y = y;
    
    _core->sendMsg(_dstIndex, (const char*)&pos, (int)sizeof(pos));
}


-(int)onInit:(int)myIp myPort:(int)port
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [_delegate onInit:myIp myPort:port];
    });
    return 0;
}

-(int)onLink:(int)srcIndex srcIp:(int)ip srcPort:(int)port srcName:(const char*)name nameSize:(int)size
{
    char* data = (char*)malloc(size);
    if(!data){
        printf("on link malloc failed, size:%d", size);
        return 0;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        [_delegate onLink:srcIndex srcIp:ip srcPort:port srcName:name nameSize:size];
        free(data);
    });
    return 0;
}

-(int)onConfirm:(int)srcIndex srcName:(const char*)name nameSize:(int)size
{
    _dstIndex = srcIndex;
    
    char* data = (char*)malloc(size);
    if(!data){
        printf("on link malloc failed, size:%d", size);
        return 0;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        [_delegate onConfirm:srcIndex srcName:name nameSize:size];
        free(data);
    });
    return 0;
}

-(int)onCancel:(int)srcIndex
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [_delegate onCancel:srcIndex];
    });
    return 0;
}

-(int)onMsg:(int)srcIndex msg:(const char*)msg  size:(int)size
{
    if(size == sizeof(struct CoreDataPos)){
        struct CoreDataPos* pos = (struct CoreDataPos*)msg;
        double x = 0;
        double y = 0;
        x = pos->x;
        y = pos->y;
        
        if(pos->header.cmd == CORE_DATA_CMD_POS_MOVE_TO){
            dispatch_async(dispatch_get_main_queue(), ^{
                [_delegate onRecvPosMoveTo:x y:y];
            });
        }
        else if(pos->header.cmd == CORE_DATA_CMD_POS_LINE_TO){
            dispatch_async(dispatch_get_main_queue(), ^{
                [_delegate onRecvPosLineTo:x y:y];
            });
        }
    }
    

    return 0;
}


@end

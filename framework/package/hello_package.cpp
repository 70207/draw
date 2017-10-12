//
//  hello_package.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <string.h>

#include "hello_package.h"
#include "hello_proto.h"
#include "../util/hello_status.h"
#include "../util/hello_log.h"

namespace hello{

    int PackageInterface::onMsgParse(int srcIp, int srcPort, int cmd, const char* msg, int size)
    {
        info("on parse message, not implemented");
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    
    void Package::init(PackageInterface* itf)
    {
        m_itf = itf;
    }
    
    void Package::parse(int srcIp, int srcPort, const char* msg, int size)
    {
        if(size < sizeof(proto::Msg)){
            return;
        }
        
        if(!msg){
            error("parse msg failed, msg pointer is null!");
            return;
        }
        
        proto::Msg* __msg = (proto::Msg*)msg;
        
        int dtSize = size - sizeof(proto::Msg);
        if(dtSize < 0){
            error("parse msg failed, msg size is wrong, msg size:%d", size);
        }
        
        if(!m_itf){
            return;
        }
        
        m_itf->onMsgParse(srcIp, srcPort, __msg->header.cmd, __msg->data, dtSize);
    
    }
    
    int Package::link(const char* myName, int size, char* buf, int& bufSize)
    {
        int __size = sizeof(proto::Header);
        if(bufSize <= __size + size){
            bufSize = __size + size;
            return HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH;
        }
        bufSize = __size + size;
        if(!buf){
            return HELLO_STATUS_OK;
        }
        
        proto::Msg*   msg = (proto::Msg*)buf;
        proto::Header* header = (proto::Header*)buf;
        header->size = __size;
        header->cmd = HELLO_PROTO_CMD_LINK;
        memcpy(msg->data, myName, size);
        
        
        return HELLO_STATUS_OK;
    }
    
    
    int Package::confirm(const char* myName, int size, char* buf, int& bufSize)
    {
        
        int __size = sizeof(proto::Header);
        if(bufSize <= __size + size){
            bufSize = __size + size;
            return HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH;
        }
        bufSize = __size + size;
        if(!buf){
            return HELLO_STATUS_OK;
        }
        
        proto::Msg*   msg = (proto::Msg*)buf;
        proto::Header* header = (proto::Header*)buf;
        header->size = __size;
        header->cmd = HELLO_PROTO_CMD_CONFIRM;
        memcpy(msg->data, myName, size);
        
        return HELLO_STATUS_OK;
    }
    
    int Package::cancel(char* buf, int& bufSize)
    {
        
        int __size = sizeof(proto::Header);
        if(bufSize <= __size){
            bufSize = __size;
            return HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH;
        }
        bufSize = __size;
        if(!buf){
            return HELLO_STATUS_OK;
        }
        
        proto::Header* header = (proto::Header*)buf;
        header->size = __size;
        header->cmd = HELLO_PROTO_CMD_CANCEL;
        return HELLO_STATUS_OK;
    }
    
    int Package::sendMsg(const char* msg, int size, char* buf, int& bufSize)
    {
        
        int __size = sizeof(proto::Msg) + size;
        if(bufSize <= __size){
            bufSize = __size;
            return HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH;
        }
        bufSize = __size;
        if(!buf){
            return HELLO_STATUS_OK;
        }
        
        proto::Header* header = (proto::Header*)buf;
        header->size = __size;
        header->cmd = HELLO_PROTO_CMD_MSG;
        
        proto::Msg*   __msg = (proto::Msg*)buf;
        memcpy(__msg->data, msg, size);
        
        return HELLO_STATUS_OK;
    }
}

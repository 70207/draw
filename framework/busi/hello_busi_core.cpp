//
//  hello_busi_core.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include "hello_busi_core.h"

#include "../package/hello_proto.h"

namespace  hello {
    
    int BC::init(hello::BusiInterface *itf){
        m_itf = itf;
        m_package.init(this);
        m_net.init(this);
        return HELLO_STATUS_OK;
    }
    
    
    
    int BC::link(const char* myName, int nameSize, int dstIp, int dstPort)
    {
        char buffer[256];
        int  bufSize = 256;
        
        int status = m_package.link(myName, nameSize, buffer, bufSize);
        if(status != HELLO_STATUS_OK){
            info("package link failed for dst ip:%d", dstIp);
            return status;
        }
        
        return m_net.sendMsg(dstIp, dstPort, buffer, bufSize);
     
    }
    
    int BC::confirm(const char* myName, int nameSize, int index)
    {
        auto it = m_clients.find(index);
        if(it == m_clients.end()){
            warn("bc confirm failed, client not found for index:%d", index);
            return HELLO_STATUS_FAIL;
        }
        
        Client& client = it->second;
        
        char buffer[256];
        int  bufSize = 256;
        
        int status = m_package.confirm(myName, nameSize, buffer, bufSize);
        if(status != HELLO_STATUS_OK){
            info("package link failed for index:%d", index);
            return status;
        }
        
        return m_net.sendMsg(client.ip, client.port, buffer, bufSize);
        
    }
    
    int BC::cancel(int index)
    {
        auto it = m_clients.find(index);
        if(it == m_clients.end()){
            warn("bc cancel failed, client not found for index:%d", index);
            return HELLO_STATUS_FAIL;
        }
        
        Client& client = it->second;
        
        char buffer[256];
        int  bufSize = 256;
        
        int status = m_package.cancel(buffer, bufSize);
        if(status != HELLO_STATUS_OK){
            info("package cancel failed for index:%d", index);
            return status;
        }
        
        return m_net.sendMsg(client.ip, client.port, buffer, bufSize);
        
    }
    
    int BC::sendMsg(int index, const char* msg, int size)
    {
        auto it = m_clients.find(index);
        if(it == m_clients.end()){
            warn("bc send msg failed, client not found for index:%d", index);
            return HELLO_STATUS_FAIL;
        }
        
        Client& client = it->second;
        
        
        char buffer[1024];
        int  bufSize = 1024;
        char* _buf = 0;
        char* buf = buffer;
        
        int status = m_package.sendMsg(msg, size, buffer, bufSize);
        if(status == HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH){
            if(bufSize > 4096){
                warn("send msg must not bigger than 4096");
                return HELLO_STATUS_MSG_TOO_BIG;
            }
            else if(bufSize <= 0){
                warn("send msg failed, package size is 0!");
                return HELLO_STATUS_PACKAGE_FAILED;
            }
            
            _buf = (char*)malloc(bufSize);
            if(!_buf){
                warn("send msg failed, malloc failed for size:%d", bufSize);
                return HELLO_STATUS_SYS_MALLOC_FAILED;
            }
            
            buf = _buf;
            
            status = m_package.sendMsg(msg, size, buffer, bufSize);
        }
        
        if(status != HELLO_STATUS_OK){
            info("package send msg failed for index:%d", index);
            free(_buf);
            return status;
        }
        
        status = m_net.sendMsg(client.ip, client.port, buffer, bufSize);
        
        free(_buf);
        
        return status;
    }
    
    int BC::onNetInit(int myIp, int myPort)
    {
        return m_itf->onInit(myIp, myPort);
    }
    
    int BC::onNetMsg(int srcIp, int srcPort, const char* msg, int size)
    {
        m_package.parse(srcIp, srcPort, msg, size);
        return HELLO_STATUS_OK;
    }
    
    
    int BC::onMsgParse(int srcIp, int srcPort, int cmd, const char* msg, int size)
    {
        long addr = srcPort << 32;
        addr |= srcIp;
        int  index = 0;
        
        auto iit = m_addrIndex.find(addr);
        if(iit == m_addrIndex.end()){
            Client client;
            m_index++;
            auto it = m_clients.insert(std::make_pair(m_index, client));
            if(it.second){
                it.first->second.ip = srcIp;
                it.first->second.port = srcPort;
                it.first->second.index = m_index;
            }
            else{
                warn("add clients failed");
                return HELLO_STATUS_FAIL;
            }
            auto jt = m_addrIndex.insert(std::make_pair(addr, m_index));
            if(!jt.second){
                warn("add client index failed");
                return HELLO_STATUS_FAIL;
            }
            
            index = m_index;
        }
        else{
            index = iit->second;
        }
        
    
        using namespace proto;
        
        switch(cmd){
            case HELLO_PROTO_CMD_LINK:
                m_itf->onLink(index, srcIp, srcPort, msg, size);
            
                break;
            case HELLO_PROTO_CMD_CONFIRM:
                m_itf->onConfirm(index, msg, size);
                break;
            case HELLO_PROTO_CMD_CANCEL:
                m_itf->onCancel(index);
                break;
            case HELLO_PROTO_CMD_MSG:
                m_itf->onMsg(index, msg, size);
                break;
                
        }
       return HELLO_STATUS_OK;
    }
    
    
}


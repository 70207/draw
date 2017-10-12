//
//  hello_busi.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include "hello_busi.h"

#include "../util/hello_log.h"
#include "../util/hello_status.h"

#include "hello_busi_core.h"


namespace hello{
    
    int BusiInterface::onInit(int myIp, int myPort)
    {
        info("not implemented, recv init, my ip :%d, my port:%d", myIp, myPort);
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    int BusiInterface::onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize)
    {
        info("not implemented, recv link from src index:%d, name:%s, name size:%d", srcIndex, srcName, nameSize);
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    
    int BusiInterface::onConfirm(int srcIndex, const char* srcName, int nameSize)
    {
        info("not implemented, recv confirm from src index:%d, src Name:%s, name size:%d", srcIndex, srcName, nameSize);
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    
    int BusiInterface::onCancel(int srcIndex)
    {
        info("not implemented, recv cancel from src index:%d", srcIndex);
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    
    int BusiInterface::onMsg(int srcIndex, const char* msg, int size)
    {
        info("not implemented, recv message from src index:%d, msg:%s, size:%d", srcIndex, msg, size);
        return HELLO_STATUS_NOT_IMPLEMENTED;
    }
    
    
    Busi::Busi():m_busi(0){
        
	}
    
    Busi::~Busi(){
        delete m_busi;
    }
    
    int Busi::init(hello::BusiInterface *itf){
        m_busi = new BC();
        return m_busi->init(itf);
    }
    
    int Busi::link(const char* myName, int nameSize, int dstIp, int dstPort){
        return m_busi->link(myName, nameSize, dstIp, dstPort);
    }
    
    int Busi::confirm(const char* srcName, int nameSize, int index)
    {
        return m_busi->confirm(srcName, nameSize, index);
    }
    
    int Busi::cancel(int index)
    {
        return m_busi->cancel(index);
    }
    
    int Busi::sendMsg(int index, const char* msg, int size)
    {
        return m_busi->sendMsg(index, msg, size);
    }
    
}

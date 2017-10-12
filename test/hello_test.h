//
//  hello_test.h
//  watchMyDraw
//
//  Created by peter chen on 2017/10/9.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_test_h
#define hello_test_h

#include "../framework/busi/hello_busi.h"
using namespace hello;

class Test : public BusiInterface{
public:
    Test();
    ~Test();
    
    void testBusi();
    void sendMsg(const char* buffer, int size);
    
private:
    
    
    int onInit(int myIp, int myPort);
    int onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize);
    int onConfirm(int srcIndex, const char* srcName, int nameSize);
    int onCancel(int srcIndex);
    int onMsg(int srcIndex, const char* msg, int size);
    
private:
    Busi*			m_busi;
    
    int 			m_dstIndex;
    char 			m_name[128];
};

#endif /* hello_test_h */

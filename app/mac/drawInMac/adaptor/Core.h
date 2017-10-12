//
//  core.hpp
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef core_hpp
#define core_hpp

#include "../../../../framework/busi/hello_busi.h"

using namespace hello;

class Core: public BusiInterface, public Busi
{
public:
    Core();
    ~Core();
    
    void init();
    
    int onInit(int myIp, int myPort);
    int onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize);
    int onConfirm(int srcIndex, const char* srcName, int nameSize);
    int onCancel(int srcIndex);
    int onMsg(int srcIndex, const char* msg, int size);
    
};


#endif /* core_hpp */

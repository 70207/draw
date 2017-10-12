//
//  hello_busi.h
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_busi_hpp
#define hello_busi_hpp

#include <stdio.h>




namespace hello{
    
    class BusiInterface{
    public:
        

        virtual int onInit(int myIp, int myPort);
        virtual int onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize);
        virtual int onConfirm(int srcIndex, const char* srcName, int nameSize);
        virtual int onCancel(int srcIndex);
        virtual int onMsg(int srcIndex, const char* msg, int size);
        
        
       
        
    };
    
    class Busi{
    public:
        Busi();
        virtual ~Busi();
        virtual int init(BusiInterface* itf);
        virtual int link(const char* myName, int nameSize, int dstIp, int dstPort);
        virtual int confirm(const char* myName, int nameSize, int index);
        virtual int cancel(int index);
        virtual int sendMsg(int index, const char* msg, int size);
        
    private:
        
        Busi*					m_busi;
        
    };
    
}

#endif /* hello_busi_h */

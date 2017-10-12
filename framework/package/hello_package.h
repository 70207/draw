//
//  hello_package.hpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_package_hpp
#define hello_package_hpp

#include <stdio.h>

namespace hello{
    class PackageInterface{
    public:
        virtual int onMsgParse(int srcIp, int srcPort,  int cmd, const char* msg, int size);
        
    };
    
    class Package{
    public:
        
        Package(){}
        ~Package(){}
        
        void init(PackageInterface* itf);
        
        void parse(int srcIp, int srcPort, const char* msg, int size);
        
        int link(const char* myName, int size, char* buf, int& bufSize);
        

        int confirm(const char* myName, int size, char* buf, int& bufSize);
        int cancel(char* buf, int& bufSize);
        int sendMsg(const char* msg, int size, char* buf, int& bufSize);
        
    private:
        
        PackageInterface*   m_itf;
        
    };
    
}


#endif /* hello_package_hpp */

//
//  hello_busi_core.hpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_busi_core_hpp
#define hello_busi_core_hpp

#include <stdio.h>
#include <unordered_map>
#include "hello_busi.h"

#include "../net/hello_net.h"
#include "../package/hello_package.h"

namespace  hello {
    
    struct Client{
        int 			index;
        int 			ip;
        int 			port;
    };
    
    
    class BC : public Busi, public NetInterface, public PackageInterface{
    public:
        BC():
        m_itf(0), m_index(0){
            
        }
        
        ~BC(){
            
        }
        
    public: //busi
        
        int init(BusiInterface* itf);
        int link(const char* myName, int nameSize, int dstIp, int dstPort);
        int confirm(const char* myName, int nameSize, int index);
        int cancel(int index);
        int sendMsg(int index, const char* msg, int size);
        
    public: //net
        int onNetMsg(int srcIp, int srcPort, const char* msg, int size);
        
    public: //package
        int onNetInit(int myIp, int myPort);
        int onMsgParse(int srcIp, int srcPort, int cmd, const char* msg, int size);
        
        
    private:
        
        
        BusiInterface*            				m_itf;
        Net                       				m_net;
        Package                   				m_package;
        int 									m_index;
        
        std::unordered_map<int, Client>			m_clients;
        std::unordered_map<int, int> 			m_addrIndex;
    };
    
}

#endif /* hello_busi_core_hpp */

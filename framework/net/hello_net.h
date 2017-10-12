//
//  hello_net.hpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_net_hpp
#define hello_net_hpp

#include <stdio.h>
#include "../util/hello_log.h"
#include "../util/hello_status.h"

namespace hello{
    class NetInterface{
    public:

        
        virtual int onNetInit(int myIp, int myPort)
        {
            info("net init, not implemented, myip :%d, port:%d", myIp, myPort);
            return HELLO_STATUS_NOT_IMPLEMENTED;
        }
        
        virtual int onNetMsg(int srcIp, int srcPort, const char* msg, int size)
        {
            info("net recv message, not implemented, recv message from src ip :%d, port:%d", srcIp, srcPort);
            return HELLO_STATUS_NOT_IMPLEMENTED;
        }
    };
    
    class Net{
    public:
        Net();
        ~Net();
        
        int init(NetInterface* itf);
        int sendMsg(int dstIp, int dstPort, const char* msg, int size);
        
    private:
        int createServer();
        void recvFunc();
        
        
     private:
        
        NetInterface*      m_itf;
        int 			   m_serverFd;
        
        
        
    };
    
}

#endif /* hello_net_hpp */

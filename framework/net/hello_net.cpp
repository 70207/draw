//
//  hello_net.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#include "hello_net.h"
#include "../util/hello_status.h"
#include "../common/hello_comm.h"
#include "../util/hello_thread.h"

namespace hello{
    static int recvdThreadRun = 0;
    
    Net::Net():m_itf(0), m_serverFd(0){
        
    }
    Net::~Net()
    {
        recvdThreadRun = 0;
    }
    
    int Net::init(NetInterface* itf)
    {
        m_itf = itf;
        return createServer();
    }
    
    int Net::sendMsg(int dstIp, int dstPort, const char* msg, int size)
    {
        if(m_serverFd <= 0){
            warn("send msg failed, server not created!");
            return HELLO_STATUS_NET_NOT_INIT;
        }
        
        struct sockaddr_in     addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = dstIp;
        if(dstPort <= 0){
            dstPort = HELLO_COMM_SERVER_LISTEN_PORT;
        }
        
        addr.sin_port = htons(dstPort);
        
        
        
        
        int status = sendto(m_serverFd, msg, size, 0, (struct sockaddr*)&addr, sizeof(addr));
        
        info("send msg to addr:%s, status:%d\n", inet_ntoa(addr.sin_addr),  status);
        
        return HELLO_STATUS_OK;
    }
    

    int Net::createServer()
    {
        int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(fd <= 0){
            warn("create server socket failed! errno:%d\n", errno);
            return HELLO_STATUS_NET_SOCKET_CREATE_FAILED;
        }
        
        struct sockaddr_in     addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;

        
        int reTimes = 10;
        int port = HELLO_COMM_SERVER_LISTEN_PORT;
        int status = 0;
        while(reTimes--){
            addr.sin_port = htons(port);
            int status = bind(fd, (const struct sockaddr*)&addr, sizeof(addr));
            if(!status){
                break;
            }
            else{
                 printf("create server socket failed! bind failed, errno:%d", errno);
            }
            port++;
        }
        
        if(status){
            warn("create server socket failed! bind failed, errno:%d", errno);
            return HELLO_STATUS_NET_SOCKET_BIND_FAILED;
        }
        
        m_serverFd = fd;
        
        
        recvdThreadRun = 1;
        Thread::createThread([this, port](){
            this->m_itf->onNetInit(0, port);
            
            while (recvdThreadRun) {
                this->recvFunc();
            }
        });
        
        return HELLO_STATUS_OK;
    }
    
    
    void Net::recvFunc()
    {
        struct sockaddr_in     addr;
        socklen_t len = sizeof(sockaddr_in);
        
        char buffer[4096];
        
        int size = (int)recvfrom(m_serverFd, buffer, 4095, 0, (sockaddr*)&addr, &len);
        if(size <= 0){
            usleep(1000);
            return;
        }
        
        if(!m_itf){
            warn("recv msg but interface not implemented");
            return;
        }
        
        info("net recv msg size:%d", size);
        
        m_itf->onNetMsg(addr.sin_addr.s_addr, ntohs(addr.sin_port),buffer, size);
        
    }
}

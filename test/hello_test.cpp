//
//  hello_test.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/9.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <limits.h>
#include <string.h>

#include "hello_test.h"
#include "../framework/util/hello_status.h"
#include "../framework/util/hello_log.h"
#include "../framework/util/hello_util.h"
#include "../framework/common/hello_comm.h"


int   g_linked = 0;

Test::Test():m_busi(0),m_dstIndex(0)
{
    
}

Test::~Test()
{
    if(m_busi){
        delete m_busi;
    }
}

void Test::testBusi()
{
    m_busi = new Busi();
    m_busi->init(this);
    
 
    char  ip[128];
    
    printf("pleast input your name\n");
    fgets(m_name, 127, stdin);
    
    
    printf("please input your select\n");
    printf("1 for link\n");
    printf("2 for auto link\n");
    int v;
    scanf("%d", &v);
    
    if(v == 1){
        printf("please input the dst ip you want link\n");
        scanf("%s", ip);
        
        int dstIp = inet_addr(ip);
        
        m_busi->link(m_name, strlen(m_name)+1, dstIp, HELLO_COMM_SERVER_LISTEN_PORT);
    }
    else{
        printf("now you can want link from others\n");
    }
    

}


void Test::sendMsg(const char *buffer, int size)
{
    m_busi->sendMsg(m_dstIndex, buffer, size);
}





int Test::onInit(int myIp, int myPort)
{
    struct in_addr addr;
    addr.s_addr = myIp;
    
    printf("on init, my ip:%s, my port:%d\n", inet_ntoa(addr), myPort);
    
    return HELLO_STATUS_OK;
    
}

int Test::onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize)
{
    struct in_addr addr;
    addr.s_addr = srcIp;
    
    printf("on link from ip:%s, port:%d, name:%s\n", inet_ntoa(addr),  srcPort, srcName);
    m_busi->confirm(m_name, strlen(m_name), srcIndex);
    printf("now you can send msg to destination\n");
    g_linked = 1;
    m_dstIndex = srcIndex;
    
    return HELLO_STATUS_OK;
}

int Test::onConfirm(int srcIndex, const char* srcName, int nameSize)
{

    printf("on confirm from index:%d, name:%s\n", srcIndex, srcName);
    m_dstIndex = srcIndex;
    printf("now you can send msg to destination\n");
    g_linked = 1;
    
    
    return HELLO_STATUS_OK;
}

int Test::onCancel(int srcIndex)
{
    printf("on cancel from index:%d\n",  srcIndex);
    return HELLO_STATUS_OK;
}
int Test::onMsg(int srcIndex, const char* msg, int size)
{
    printf("on msg from index:%d, msg: size:%d\n", srcIndex, size);
    printf("msg:%s", msg);
    return HELLO_STATUS_OK;
}

using namespace hello;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
#ifdef __APPLE__
    std::function<void(const char* buffer, int size)>   func = [](const char* buffer, int size){
       // printf("%s", buffer);
    };
    
    setlogproc(func);
    
#else
    char path[PATH_MAX];
    char processname[1024];
    std::string logFileName;
    

    
    getExecutablePath(path, processname, sizeof(path));
    
    logFileName.assign(path);
    
    logFileName.append("../log/hello.log");
    
    
    setlogpath(logFileName);
    setloglevel("debug");
#endif
    
    Test test;
    test.testBusi();
    
    while(1){
        if(g_linked){
            char buffer[1024];
            fgets(buffer, 1023, stdin);
            if(buffer[0] == '\n'){
                continue;
            }
            test.sendMsg(buffer, strlen(buffer) + 1);
        }
        else{
        	usleep(100000);
        }
    }
    
    return 0;
}

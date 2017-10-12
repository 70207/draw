//
//  core.cpp
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include "Core.h"
#import "CoreAdaptor.h"


Core::Core()
{
    
}

Core::~Core()
{
    
}

void Core::init()
{
    //init(this);
    Busi::init(this);
}




int Core::onInit(int myIp, int myPort)
{
    [[CoreAdaptor sharedCoreAdaptor] onInit:myIp myPort:myPort];
    return 0;
}

int Core::onLink(int srcIndex, int srcIp, int srcPort, const char* srcName, int nameSize)
{
    [[CoreAdaptor sharedCoreAdaptor] onLink:srcIndex srcIp:srcIp srcPort:srcPort srcName:srcName nameSize:nameSize];
    return 0;
}

int Core::onConfirm(int srcIndex, const char* srcName, int nameSize)
{
    [[CoreAdaptor sharedCoreAdaptor] onConfirm:srcIndex srcName:srcName nameSize:nameSize];
    return 0;
}

int Core::onCancel(int srcIndex)
{
    [[CoreAdaptor sharedCoreAdaptor] onCancel:srcIndex];
    return 0;
}

int Core::onMsg(int srcIndex, const char* msg, int size)
{
    [[CoreAdaptor sharedCoreAdaptor] onMsg:srcIndex msg:msg size:size];
    return 0;
}

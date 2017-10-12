//
//  hello_util.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/9.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <chrono>
#include <string>
#include <fcntl.h>


#include "hello_util.h"


namespace hello{
    
    size_t getExecutablePath( char* processDir,char* processName, size_t len)
    {
        char* path_end;
        memset(processDir, 0, len);
        if(readlink("/proc/self/exe", processDir,len) <=0)
            return -1;
        path_end = strrchr(processDir,  '/');
        if(path_end == NULL)
            return -1;
        ++path_end;
        strcpy(processName, path_end);
        *path_end = '\0';
        return (size_t)(path_end - processDir);
    }
    
    
}

//
//  hello_thread.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <algorithm>
#include <thread>
#include <vector>
#include <string.h>

#include "hello_thread.h"
#include "hello_status.h"



#ifdef linux
#define gettid() syscall(__NR_gettid)
#endif

namespace hello{
    namespace Thread{
        long long getThreadID()
        {
#ifdef linux
            return gettid();
#else
            
            pthread_t tid = pthread_self();
            uint64_t uid = 0;
            memcpy(&uid, &tid, std::min(sizeof(tid), sizeof(uid)));
            return uid;
#endif
        }
        
        std::vector<std::thread>              threads;
        static int  thread_reserve = 0;
        static int 	thread_count = 0;
        
        int createThread( std::function<void()> func )
        {
            if(thread_count >= thread_reserve){
                thread_reserve += 8;
                threads.reserve(thread_reserve);
            }
            
            
            
            std::thread t([func]{
                func();
            });
            
            
            threads[thread_count++].swap(t);
            
            return HELLO_STATUS_OK;
        }
    }
}

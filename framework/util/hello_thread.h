//
//  hello_thread.hpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_thread_hpp
#define hello_thread_hpp

#include <stdio.h>
#include <functional>



namespace hello{
    namespace Thread{

        
        
        long long getThreadID();
        int createThread( std::function<void()> func );
        
    
    };
}

#endif /* hello_thread_hpp */

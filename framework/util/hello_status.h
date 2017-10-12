//
//  hello_status.hpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_status_hpp
#define hello_status_hpp

#include <stdio.h>

namespace hello{
#define HELLO_STATUS_OK    				 	 		0
#define HELLO_STATUS_FAIL					 		1


//FUNC
#define HELLO_STATUS_NOT_IMPLEMENTED         		101
    
//SYS
#define HELLO_STATUS_SYS_MALLOC_FAILED 				201
    
//PACKAGE
#define HELLO_STATUS_PACKAGE_FAILED					301
  
//MSG
#define HELLO_STATUS_MSG_TOO_BIG					401
    
//PROTO
#define HELLO_STATUS_PROTO_BUFFER_NOT_ENOUGH 		501
    
//net
#define HELLO_STATUS_NET_NOT_INIT					601
#define HELLO_STATUS_NET_SOCKET_CREATE_FAILED		602
#define HELLO_STATUS_NET_SOCKET_BIND_FAILED			603
    
    
}

#endif /* hello_status_hpp */

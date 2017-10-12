//
//  hello_proto.h
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef hello_proto_h
#define hello_proto_h


namespace hello{
    namespace proto{
#pragma  pack(1)
        struct Header{
            int 			size;
            int 			cmd;
        };
        

        
        struct Msg{
            Header 			header;
            char 			data[0];
        };
#pragma  pack()
        
        
#define HELLO_PROTO_CMD_LINK				1
#define HELLO_PROTO_CMD_CONFIRM				2
#define HELLO_PROTO_CMD_CANCEL			    3
#define HELLO_PROTO_CMD_MSG					4
    }
}

#endif /* hello_proto_h */

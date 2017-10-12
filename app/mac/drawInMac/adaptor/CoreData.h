//
//  ViewData.h
//  drawInMac
//
//  Created by peter chen on 2017/10/11.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#ifndef ViewData_h
#define ViewData_h

#define CORE_DATA_CMD_POS_MOVE_TO 1
#define CORE_DATA_CMD_POS_LINE_TO 2

#pragma pack(1)

struct CoreDataHeader{
    int			cmd;
};

struct CoreDataPos{
    struct CoreDataHeader   header;
    double 			 		x;
    double 			 		y;
};

#pragma pack()


#endif /* ViewData_h */

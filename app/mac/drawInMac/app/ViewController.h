//
//  ViewController.h
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <SpriteKit/SpriteKit.h>
#import <GameplayKit/GameplayKit.h>

#include "../adaptor/CoreDelegate.h"
#include "../adaptor/CoreAdaptor.h"

@interface ViewController<CoreDelegate> : NSViewController

@property (assign) IBOutlet SKView *skView;

@property (weak) IBOutlet NSButton *btnConnect;
@property (weak) IBOutlet NSTextField *txtDstIp;
@property (weak) IBOutlet NSTextField *txtDstPort;

@property (weak) IBOutlet NSTextField *lbMyIp;
@property (weak) IBOutlet NSTextField *lbMyPort;
@property (weak) IBOutlet NSTextField *lbMyID;


@property (weak) IBOutlet NSBox *boxMain;


@property (weak) IBOutlet NSBox *boxPop;


@property (weak) IBOutlet NSTextField *lbConnectFromIp;
@property (weak) IBOutlet NSTextField *lbConnectFromPort;
@property (weak) IBOutlet NSTextField *lbConnectFromID;

@property (weak) IBOutlet NSButton *btnApprove;
@property (weak) IBOutlet NSButton *btnCancel;



@property (weak) IBOutlet NSBox *boxConnecting;

@property (weak) IBOutlet NSView *boxStatus;
@property (weak) IBOutlet NSTextField *lbStatus;






@end


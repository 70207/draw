//
//  ViewController.m
//  drawInMac
//
//  Created by peter chen on 2017/10/10.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//


#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



#import "../util/Util.h"

#import "ViewController.h"



#import "GameScene.h"
#import "CanvasScene.h"




@implementation ViewController 
{
    GameScene*			_gs;
    CanvasScene*		_cs;
    
    int 				_myIp;
    int 				_myPort;
    
    int 			    _waitConfirmIndex;
    
    NSString*		    _myName;
    NSString* 			_dstName;

    
}

- (void)dataInit{
    _myIp = 0;
    _myPort = 0;
    _waitConfirmIndex = 0;
    _myName = 0;
    _dstName = 0;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    CGSize size = self.view.frame.size;
    // Load the SKScene from 'GameScene.sks'
    _gs = [[GameScene alloc] initWithSize:size];//(GameScene *)[SKScene nodeWithFileNamed:@"GameScene"];
    [_gs setBackgroundColor:[NSColor whiteColor]];
    _cs = [[CanvasScene alloc] initWithSize:size];
    [_cs initView];
    
    
    _gs.scaleMode = SKSceneScaleModeAspectFill;
    _gs.scaleMode = SKSceneScaleModeAspectFill;
    
    // Present the scene
    [self.skView presentScene:_gs];
    
    self.skView.showsFPS = YES;
    self.skView.showsNodeCount = YES;
    

    [_boxConnecting setHidden:YES];
    [_boxPop setHidden:YES];
    
    [_btnConnect setTarget:self];
    [_btnConnect setAction:@selector(connect:)];
    
    [_btnApprove setTarget:self];
    [_btnApprove setAction:@selector(confirm:)];
    
    [_btnCancel setTarget:self];
    [_btnCancel setAction:@selector(cancel:)];
    
    [_boxStatus setHidden:YES];
    
    
     [self dataInit];
    
    NSString* ip = [Util getIPAddress];
    const char* myIp = [ip UTF8String];
    _myIp = inet_addr(myIp);
    
    [[CoreAdaptor sharedCoreAdaptor] setDelegate:self];
    [[CoreAdaptor sharedCoreAdaptor] coreInit];
    

   
    
}




- (IBAction)connect:(id)sender {
    if(_lbMyID.stringValue.length <= 0){
        [_lbStatus setStringValue:@"填写我的ID"];
        [_boxStatus setHidden:NO];
        
        return;
    }
    
    if(_txtDstIp.stringValue.length <= 0){
        [_lbStatus setStringValue:@"填写对方IP"];
        [_boxStatus setHidden:NO];
        
        return;
    }
    
    if(_txtDstPort.stringValue.length <= 0){
        [_lbStatus setStringValue:@"填写对方端口"];
        [_boxStatus setHidden:NO];
        
        return;
    }
    
    
    [_boxMain setHidden:YES];
    [_boxPop setHidden:YES];
    [_boxConnecting setHidden:NO];
    
    _myName = _lbMyID.stringValue;
    
    NSString* str = _txtDstIp.stringValue;
    const char* ip = [str UTF8String];
    const char* port = [_txtDstPort.stringValue UTF8String];
    
    const char* name = [_lbMyID.stringValue UTF8String];
    int nameSize = _lbMyID.stringValue.length;
    
    int dstIp = inet_addr(ip);
    int dstPort = atoi(port);
    
    [[CoreAdaptor sharedCoreAdaptor] link:name nameSize:nameSize dstIp:dstIp dstPort:dstPort];

}

- (IBAction)confirm:(id)sender {
    if(_lbMyID.stringValue.length <= 0){
        [_lbStatus setStringValue:@"填写我的ID"];
        [_boxStatus setHidden:NO];

        return;
    }
    
    _myName = _lbMyID.stringValue;
    
    [_boxStatus setHidden:YES];
    [_boxMain setHidden:YES];
    [_boxPop setHidden:YES];
    [_boxConnecting setHidden:YES];
    
    [self start:_myName dstName:_dstName];
    
   
    [[CoreAdaptor sharedCoreAdaptor] confirm:[_lbMyID.stringValue UTF8String] nameSize:_lbMyID.stringValue.length dstIndex:_waitConfirmIndex];

    
}


- (IBAction)cancel:(id)sender {
    [_boxStatus setHidden:YES];
    [_boxMain setHidden:NO];
    [_boxPop setHidden:YES];
    [_boxConnecting setHidden:YES];
    
    [self.skView presentScene:_gs];
    
    
   
    [[CoreAdaptor sharedCoreAdaptor] cancel:_waitConfirmIndex];
}




-(void)start:(NSString*)myName dstName:(NSString*)name
{
    [_cs setName:myName dstName:name];
    [self.skView presentScene:_cs];
}



-(int)onInit:(int)myIp myPort:(int)port
{
    struct in_addr addr;
    addr.s_addr = myIp;
    const char* ip = inet_ntoa(addr);
    [_lbMyIp setStringValue:[NSString stringWithFormat:@"%s", ip]];
    [_lbMyPort setStringValue:[NSString stringWithFormat:@"%d", port]];
    

    _myPort = port;
    
    return 0;
}

-(void)onLink:(int)srcIndex srcIp:(int)ip srcPort:(int)port srcName:(const char*)name nameSize:(int)size
{
    NSString* dstName = [NSString stringWithFormat:@"%s", name];
    _dstName = dstName;
    
    _waitConfirmIndex = srcIndex;
    struct in_addr addr;
    addr.s_addr = ip;
    const char* _sip = inet_ntoa(addr);
   
    [_lbConnectFromIp setStringValue:[NSString stringWithFormat:@"%s", _sip]];
    [_lbConnectFromPort setStringValue:[NSString stringWithFormat:@"%d", port]];
   
    [_boxStatus setHidden:YES];
    [_boxPop setHidden:NO];
    [_boxConnecting setHidden:YES];
}

-(void)onConfirm:(int)srcIndex srcName:(const char*)name nameSize:(int)size
{
    [_boxStatus setHidden:YES];
    [_boxMain setHidden:YES];
    [_boxPop setHidden:YES];
    [_boxConnecting setHidden:YES];
    
    _dstName = [NSString stringWithFormat:@"%s", name];
    
    [self start:_myName dstName:_dstName];
 
}

-(void)onCancel:(int)srcIp srcPort:(int)port
{
    [_boxStatus setHidden:YES];
    [_boxMain setHidden:NO];
    [_boxPop setHidden:YES];
    [_boxConnecting setHidden:YES];
    
    [self.skView presentScene:_gs];
}

-(void)onRecvPosMoveTo:(double)x  y:(double)y
{
    CGPoint pt;
    pt.x = x;
    pt.y = y;
    [_cs syncMoveToPoint:pt];
}

-(void)onRecvPosLineTo:(double)x  y:(double)y
{
    CGPoint pt;
    pt.x = x;
    pt.y = y;
    [_cs syncLineToPoint:pt];
}


@end

//
//  PLMainViewController.m
//  PLCameraStreamingKitDemo
//
//  Created by TaoZeyu on 16/5/27.
//  Copyright © 2016年 Pili. All rights reserved.
//

#import "PLMainViewController.h"

#import <PLMediaStreamingKit/PLMediaStreamingKit.h>

/** faceU */
#import "FUDemoManager.h"

@interface PLMainViewController ()<PLMediaStreamingSessionDelegate>

@property(nonatomic, strong) PLMediaStreamingSession *session;

@end

@implementation PLMainViewController


- (void)dealloc{

    if (self.isuseFU) {
        
        [[FUManager shareManager] destoryItems];
    }
    [self.session destroy];
    
}


- (void)viewDidLoad{
    
    [super viewDidLoad];
    self.navigationItem.title = self.roomId;
    self.view.backgroundColor = [UIColor whiteColor];
    UIButton *caremaBtn = [[UIButton alloc] init];
    [caremaBtn setTitle:@"相机" forState:(UIControlStateNormal)];
    [caremaBtn sizeToFit];
    [caremaBtn setTitleColor:[UIColor blueColor] forState:(UIControlStateNormal)];
    [caremaBtn addTarget:self action:@selector(caremaBtnClick:) forControlEvents:(UIControlEventTouchUpInside)];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:caremaBtn];
    
    // 初始化模块
    [self setupSession];
    if (self.isuseFU) {
        // FaceUnity UI
        CGFloat safeAreaBottom = 0;
        if (@available(iOS 11.0, *)) {
            safeAreaBottom = [UIApplication sharedApplication].delegate.window.safeAreaInsets.bottom;
        }
        [FUDemoManager setupFaceUnityDemoInController:self originY:CGRectGetHeight(self.view.frame) - FUBottomBarHeight - safeAreaBottom];
    }
}

- (void)setupSession{
    
    // 创建视频和音频的采集和编码配置对象
    PLVideoCaptureConfiguration *videoCaptureConfiguration = [PLVideoCaptureConfiguration defaultConfiguration];
    videoCaptureConfiguration.position = AVCaptureDevicePositionFront;
    videoCaptureConfiguration.videoFrameRate = 30;
    videoCaptureConfiguration.sessionPreset = AVCaptureSessionPreset1280x720;
    videoCaptureConfiguration.streamMirrorFrontFacing = YES;
    PLAudioCaptureConfiguration *audioCaptureConfiguration = [PLAudioCaptureConfiguration defaultConfiguration];
    PLVideoStreamingConfiguration *videoStreamingConfiguration = [PLVideoStreamingConfiguration defaultConfiguration];
    videoStreamingConfiguration.videoSize = CGSizeMake(720, 1280);
    
    PLAudioStreamingConfiguration *audioStreamingConfiguration = [PLAudioStreamingConfiguration defaultConfiguration];

    // 创建推流 session 对象
    self.session = [[PLMediaStreamingSession alloc] initWithVideoCaptureConfiguration:videoCaptureConfiguration audioCaptureConfiguration:audioCaptureConfiguration videoStreamingConfiguration:videoStreamingConfiguration audioStreamingConfiguration:audioStreamingConfiguration stream:nil];
    self.session.delegate = self;

    // 将预览视图添加为当前视图的子视图
    [self.view addSubview:self.session.previewView];
    

    // 推流地址
    NSString *pushStr = [NSString stringWithFormat:@"rtmp://pili-publish.xuzhuolalala.support2technical.me/xuzhuo-lalala/qiniu_test/%@",self.roomId];
    NSURL *pushURL = [NSURL URLWithString:pushStr];
    
    // 开始推流
    [self.session startStreamingWithPushURL:pushURL feedback:^(PLStreamStartStateFeedback feedback) {

        if (feedback == PLStreamStartStateSuccess) {

            NSLog(@"Streaming started.");

        }
        else {

            NSLog(@"Oops.");
        }

    }];
    
}

/**     -----  FaceUnity  ----     **/
- (CVPixelBufferRef)mediaStreamingSession:(PLMediaStreamingSession *)session cameraSourceDidGetPixelBuffer:(CVPixelBufferRef)pixelBuffer timingInfo:(CMSampleTimingInfo)timingInfo{
    
    if (self.isuseFU) {
        
        pixelBuffer = [[FUManager shareManager] renderItemsToPixelBuffer:pixelBuffer];
    }
    
    return pixelBuffer;
}

/// 切换摄像头
/// @param caremaBtn caremaBtn
- (void)caremaBtnClick:(UIButton *)caremaBtn{
    
    [self.session toggleCamera];
    
    if (self.isuseFU) {
      
        [[FUManager shareManager] onCameraChange];
    }
    
}

@end

//
//  PLMainViewController.m
//  PLCameraStreamingKitDemo
//
//  Created by TaoZeyu on 16/5/27.
//  Copyright © 2016年 Pili. All rights reserved.
//

#import "PLMainViewController.h"

#import <PLMediaStreamingKit/PLMediaStreamingKit.h>
#import <Masonry/Masonry.h>

/** faceU */
#import "FUDemoManager.h"

@interface PLMainViewController ()<PLMediaStreamingSessionDelegate>

@property(nonatomic, strong) PLMediaStreamingSession *session;

@end

@implementation PLMainViewController



- (void)viewDidLoad{
    
    [super viewDidLoad];
    self.navigationItem.title = self.roomId;
    self.view.backgroundColor = [UIColor whiteColor];
    
    UIButton *backBtn = [[UIButton alloc] init];
    [backBtn setTitle:@"返回" forState:(UIControlStateNormal)];
    [backBtn sizeToFit];
    [backBtn setTitleColor:[UIColor blueColor] forState:(UIControlStateNormal)];
    [backBtn addTarget:self action:@selector(backBtnClick:) forControlEvents:(UIControlEventTouchUpInside)];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backBtn];
    
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
        [FUDemoManager setupFUSDK];
        [[FUDemoManager shared] addDemoViewToView:self.view originY:CGRectGetHeight(self.view.bounds) - FUBottomBarHeight - FUSafaAreaBottomInsets()];
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

    // 添加预览视图到父视图
    [self.view insertSubview:_session.previewView atIndex:0];
    
    // 配置采集预览视图 frame
    [_session.previewView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.insets = UIEdgeInsetsZero;
    }];
    
    // 遵守代理 PLMediaStreamingSessionDelegate
    _session.delegate = self;
    [_session setBeautifyModeOn:NO];
    
    // 推流地址
    NSString *pushStr = [NSString stringWithFormat:@"rtmp://pili-publish.qnsdk.com/sdk-live/faceunitytest/%@",self.roomId];
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
    
        [[FUDemoManager shared] checkAITrackedResult];
        if ([FUDemoManager shared].shouldRender) {
            [[FUTestRecorder shareRecorder] processFrameWithLog];
            [FUDemoManager updateBeautyBlurEffect];
            FURenderInput *input = [[FURenderInput alloc] init];
            input.renderConfig.imageOrientation = FUImageOrientationUP;
            input.pixelBuffer = pixelBuffer;
            //开启重力感应，内部会自动计算正确方向，设置fuSetDefaultRotationMode，无须外面设置
            input.renderConfig.gravityEnable = YES;
            FURenderOutput *output = [[FURenderKit shareRenderKit] renderWithInput:input];
            if (output) {
                return output.pixelBuffer;
            }
        } else {
            return pixelBuffer;
        }
    }
    
    return pixelBuffer;
}

/// 返回
/// @param backBtn caremaBtn
- (void)backBtnClick:(UIButton *)backBtn{
    
    [self.session destroy];
    if (self.isuseFU) {
        [FUDemoManager destory];
    }
    [self.navigationController popViewControllerAnimated:YES];
    
}

/// 切换摄像头
/// @param caremaBtn caremaBtn
- (void)caremaBtnClick:(UIButton *)caremaBtn{
    
    [self.session toggleCamera];
    
    if (self.isuseFU) {
      
        [FUDemoManager resetTrackedResult];
    }
    
}

@end

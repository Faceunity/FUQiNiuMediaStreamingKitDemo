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
#import "FUManager.h"
#import "FUAPIDemoBar.h"

#import "FUTestRecorder.h"



@interface PLMainViewController ()<PLMediaStreamingSessionDelegate,FUAPIDemoBarDelegate>

@property(nonatomic, strong) PLMediaStreamingSession *session;


/**faceU */
@property (nonatomic, strong) FUAPIDemoBar *demoBar;


@end

@implementation PLMainViewController


- (void)dealloc{

    [[FUManager shareManager] destoryItems];
    [self.session destroy];
    
}


- (void)viewDidLoad{
    
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    UIButton *caremaBtn = [[UIButton alloc] init];
    [caremaBtn setTitle:@"相机" forState:(UIControlStateNormal)];
    [caremaBtn sizeToFit];
    [caremaBtn setTitleColor:[UIColor blueColor] forState:(UIControlStateNormal)];
    [caremaBtn addTarget:self action:@selector(caremaBtnClick:) forControlEvents:(UIControlEventTouchUpInside)];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:caremaBtn];
    
    // 初始化模块
    [self setupSession];
    
    // FU
    [self setupFaceUnity];
    
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
/// faceunity
- (void)setupFaceUnity{

    [[FUTestRecorder shareRecorder] setupRecord];
    
    [[FUManager shareManager] loadFilter];
    [FUManager shareManager].flipx = YES;
    [FUManager shareManager].trackFlipx = YES;
    [FUManager shareManager].isRender = YES;
    
    _demoBar = [[FUAPIDemoBar alloc] init];
    _demoBar.mDelegate = self;
    [self.view addSubview:_demoBar];
    [_demoBar mas_makeConstraints:^(MASConstraintMaker *make) {
        
        if (@available(iOS 11.0, *)) {
           
            make.left.mas_equalTo(self.view.mas_safeAreaLayoutGuideLeft);
            make.right.mas_equalTo(self.view.mas_safeAreaLayoutGuideRight);
            make.bottom.mas_equalTo(self.view.mas_safeAreaLayoutGuideBottom);
        
        } else {
        
            make.left.right.bottom.mas_equalTo(0);
        }

        make.height.mas_equalTo(195);
        
    }];
    
}
/**      FUAPIDemoBarDelegate       **/

-(void)filterValueChange:(FUBeautyParam *)param{
    [[FUManager shareManager] filterValueChange:param];
}

-(void)switchRenderState:(BOOL)state{
    [FUManager shareManager].isRender = state;
}

-(void)bottomDidChange:(int)index{
    if (index < 3) {
        [[FUManager shareManager] setRenderType:FUDataTypeBeautify];
    }
    if (index == 3) {
        [[FUManager shareManager] setRenderType:FUDataTypeStrick];
    }
    
    if (index == 4) {
        [[FUManager shareManager] setRenderType:FUDataTypeMakeup];
    }
    if (index == 5) {
        [[FUManager shareManager] setRenderType:FUDataTypebody];
    }
}


/**     -----  FaceUnity  ----     **/

- (CVPixelBufferRef)mediaStreamingSession:(PLMediaStreamingSession *)session cameraSourceDidGetPixelBuffer:(CVPixelBufferRef)pixelBuffer timingInfo:(CMSampleTimingInfo)timingInfo{
    
    [[FUTestRecorder shareRecorder] processFrameWithLog];
    CVPixelBufferRef buffer = [[FUManager shareManager] renderItemsToPixelBuffer:pixelBuffer];
    return buffer;
}




/// 切换摄像头
/// @param caremaBtn caremaBtn
- (void)caremaBtnClick:(UIButton *)caremaBtn{
    
    [self.session toggleCamera];
    [[FUManager shareManager] onCameraChange];
}

@end

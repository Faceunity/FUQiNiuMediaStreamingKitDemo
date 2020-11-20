# FUQiNiuMediaStreamingKitDemo 快速接入文档

FUQiNiuMediaStreamingKitDemo 是集成了 [Faceunity](https://github.com/Faceunity/FULiveDemo/tree/dev) 面部跟踪和虚拟道具功能 和 七牛推流 功能的 Demo。

**本文是 FaceUnity SDK  快速对接 七牛推流 的导读说明**

**关于  FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo/tree/dev)**


## 快速集成方法

### 一、导入 SDK

将  FaceUnity  文件夹全部拖入工程中，NamaSDK所需依赖库为 `OpenGLES.framework`、`Accelerate.framework`、`CoreMedia.framework`、`AVFoundation.framework`、`libc++.tbd`、`CoreML.framework`

- 备注: 上述NamaSDK 依赖库使用 Pods 管理 会自动添加依赖,运行在iOS11以下系统时,需要手动添加`CoreML.framework`,并在**TARGETS -> Build Phases-> Link Binary With Libraries**将`CoreML.framework`手动修改为可选**Optional**

### FaceUnity 模块简介

```objc
-FUManager          //nama 业务类
-FUCamera           //视频采集类 (示例程序未使用) 
-authpack.h         //权限文件  
+FUAPIDemoBar     //美颜工具条,可自定义
+items            //美妆贴纸 xx.bundel文件

```

### 二、加入展示 FaceUnity SDK 美颜贴纸效果的  UI

1、在  PLMainViewController.m  中添加头文件，并创建页面属性

```C
#import "FUManager.h"
#import "FUAPIDemoBar.h"

@property (nonatomic, strong) FUAPIDemoBar *demoBar ;
```

2、初始化 UI，并遵循代理  FUAPIDemoBarDelegate ，实现代理方法 `bottomDidChange:` 切换贴纸 和 `filterValueChange:` 更新美颜参数。

#### 切换贴纸

```C
// 切换贴纸
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

```

#### 更新美颜参数

```C
// 更新美颜参数
-(void)filterValueChange:(FUBeautyParam *)param{
    [[FUManager shareManager] filterValueChange:param];
}
```

### 二、在 `viewDidLoad:` 中调用`setupFaceUnity`初始化 SDK  并将  demoBar 添加到页面上

```C

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
```

### 三、在视频数据回调中 加入 FaceUnity  的数据处理

在创建推流 session 对象时,设置PLMediaStreamingSessionDelegate

```C
- (CVPixelBufferRef)mediaStreamingSession:(PLMediaStreamingSession *)session cameraSourceDidGetPixelBuffer:(CVPixelBufferRef)pixelBuffer timingInfo:(CMSampleTimingInfo)timingInfo{
    
    [[FUTestRecorder shareRecorder] processFrameWithLog];
    CVPixelBufferRef buffer = [[FUManager shareManager] renderItemsToPixelBuffer:pixelBuffer];
    return buffer;
}
```
### 四、推流结束时需要销毁道具

销毁道具需要调用以下代码

```C
[[FUManager shareManager] destoryItems];
```

切换摄像头调用一下代码
```C
 [[FUManager shareManager] onCameraChange];切换摄像头
```

### 关于 FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo/tree/dev)
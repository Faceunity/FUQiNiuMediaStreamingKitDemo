# FUQiNiuMediaStreamingKitDemo 快速接入文档

FUQiNiuMediaStreamingKitDemo 是集成了 [Faceunity](https://github.com/Faceunity/FULiveDemo) 面部跟踪和虚拟道具功能 和 七牛推流 功能的 Demo。

**本文是 FaceUnity SDK  快速对接 七牛推流 的导读说明**

**关于  FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo)**


## 快速集成方法

### 一、导入 SDK

将  FaceUnity  文件夹全部拖入工程中，NamaSDK所需依赖库为 `OpenGLES.framework`、`Accelerate.framework`、`CoreMedia.framework`、`AVFoundation.framework`、`libc++.tbd`、`CoreML.framework`

- 备注: 运行在iOS11以下系统时,需要手动添加`CoreML.framework`,并在**TARGETS -> Build Phases-> Link Binary With Libraries**将`CoreML.framework`手动修改为可选**Optional**

### FaceUnity 模块简介

```objc
+ Abstract          // 美颜参数数据源业务文件夹
    + FUProvider    // 美颜参数数据源提供者
    + ViewModel     // 模型视图参数传递者
-FUManager          //nama 业务类
-authpack.h         //权限文件  
+FUAPIDemoBar     //美颜工具条,可自定义
+items            //美妆贴纸 xx.bundel文件

```

### 二、加入展示 FaceUnity SDK 美颜贴纸效果的  UI

1、在  PLMainViewController.m  中添加头文件
```objc
#import "FUDemoManager.h"

```

2、在 `viewDidLoad` 方法中初始化FU `setupFaceUnityDemoInController` 会初始化FUSDK,和添加美颜工具条,具体实现可查看 `FUDemoManager.m`
```objc
        // FaceUnity UI
        CGFloat safeAreaBottom = 0;
        if (@available(iOS 11.0, *)) {
            safeAreaBottom = [UIApplication sharedApplication].delegate.window.safeAreaInsets.bottom;
        }
        [FUDemoManager setupFaceUnityDemoInController:self originY:CGRectGetHeight(self.view.frame) - FUBottomBarHeight - safeAreaBottom];
```

### 三、在视频数据回调中 加入 FaceUnity  的数据处理

在创建推流 session 对象时,设置PLMediaStreamingSessionDelegate

```C
- (CVPixelBufferRef)mediaStreamingSession:(PLMediaStreamingSession *)session cameraSourceDidGetPixelBuffer:(CVPixelBufferRef)pixelBuffer timingInfo:(CMSampleTimingInfo)timingInfo{

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

### 关于 FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo)

# FUQiNiuMediaStreamingKitDemo 快速接入文档

FUQiNiuMediaStreamingKitDemo 是集成了 [Faceunity](https://github.com/Faceunity/FULiveDemo/tree/dev) 面部跟踪和虚拟道具功能 和 七牛推流 功能的 Demo。

**本文是 FaceUnity SDK  快速对接 七牛推流 的导读说明**

**关于  FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo/tree/dev)**



## 快速集成方法

### 一、导入 SDK
将  FaceUnity  文件夹全部拖入工程中，并且添加依赖库 `OpenGLES.framework`、`Accelerate.framework`、`CoreMedia.framework`、`AVFoundation.framework`、`stdc++.tbd`

### 二、加入展示 FaceUnity SDK 美颜贴纸效果的  UI

1、在  PLMainViewController.m  中添加头文件，并创建页面属性

```C
#import <FUAPIDemoBar/FUAPIDemoBar.h>

@property (nonatomic, strong) FUAPIDemoBar *demoBar ;
```

2、初始化 UI，并遵循代理  FUAPIDemoBarDelegate ，实现代理方法 `demoBarDidSelectedItem:` 切换贴纸 和 `demoBarBeautyParamChanged` 更新美颜参数。

```C
// demobar 初始化
-(FUAPIDemoBar *)demoBar {
    if (!_demoBar) {
        
        _demoBar = [[FUAPIDemoBar alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - 164 - 44, self.view.frame.size.width, 164)];
        
        _demoBar.itemsDataSource = [FUManager shareManager].itemsDataSource;
        _demoBar.selectedItem = [FUManager shareManager].selectedItem ;
        
        _demoBar.filtersDataSource = [FUManager shareManager].filtersDataSource ;
        _demoBar.beautyFiltersDataSource = [FUManager shareManager].beautyFiltersDataSource ;
        _demoBar.filtersCHName = [FUManager shareManager].filtersCHName ;
        _demoBar.selectedFilter = [FUManager shareManager].selectedFilter ;
        [_demoBar setFilterLevel:[FUManager shareManager].selectedFilterLevel forFilter:[FUManager shareManager].selectedFilter] ;
        
        _demoBar.skinDetectEnable = [FUManager shareManager].skinDetectEnable;
        _demoBar.blurShape = [FUManager shareManager].blurShape ;
        _demoBar.blurLevel = [FUManager shareManager].blurLevel ;
        _demoBar.whiteLevel = [FUManager shareManager].whiteLevel ;
        _demoBar.redLevel = [FUManager shareManager].redLevel;
        _demoBar.eyelightingLevel = [FUManager shareManager].eyelightingLevel ;
        _demoBar.beautyToothLevel = [FUManager shareManager].beautyToothLevel ;
        _demoBar.faceShape = [FUManager shareManager].faceShape ;
        
        _demoBar.enlargingLevel = [FUManager shareManager].enlargingLevel ;
        _demoBar.thinningLevel = [FUManager shareManager].thinningLevel ;
        _demoBar.enlargingLevel_new = [FUManager shareManager].enlargingLevel ;
        _demoBar.thinningLevel_new = [FUManager shareManager].thinningLevel ;
        _demoBar.jewLevel = [FUManager shareManager].jewLevel ;
        _demoBar.foreheadLevel = [FUManager shareManager].foreheadLevel ;
        _demoBar.noseLevel = [FUManager shareManager].noseLevel ;
        _demoBar.mouthLevel = [FUManager shareManager].mouthLevel ;
        
        _demoBar.delegate = self;
    }
    return _demoBar ;
}
```

#### 切换贴纸

```C
// 切换贴纸
- (void)demoBarDidSelectedItem:(NSString *)itemName {
    
    [[FUManager shareManager] loadItem:itemName];
}
```

#### 更新美颜参数

```C
// 更新美颜参数
- (void)demoBarBeautyParamChanged {
    
    [FUManager shareManager].skinDetectEnable = _demoBar.skinDetectEnable;
    [FUManager shareManager].blurShape = _demoBar.blurShape;
    [FUManager shareManager].blurLevel = _demoBar.blurLevel ;
    [FUManager shareManager].whiteLevel = _demoBar.whiteLevel;
    [FUManager shareManager].redLevel = _demoBar.redLevel;
    [FUManager shareManager].eyelightingLevel = _demoBar.eyelightingLevel;
    [FUManager shareManager].beautyToothLevel = _demoBar.beautyToothLevel;
    [FUManager shareManager].faceShape = _demoBar.faceShape;
    [FUManager shareManager].enlargingLevel = _demoBar.enlargingLevel;
    [FUManager shareManager].thinningLevel = _demoBar.thinningLevel;
    [FUManager shareManager].enlargingLevel_new = _demoBar.enlargingLevel_new;
    [FUManager shareManager].thinningLevel_new = _demoBar.thinningLevel_new;
    [FUManager shareManager].jewLevel = _demoBar.jewLevel;
    [FUManager shareManager].foreheadLevel = _demoBar.foreheadLevel;
    [FUManager shareManager].noseLevel = _demoBar.noseLevel;
    [FUManager shareManager].mouthLevel = _demoBar.mouthLevel;
    
    [FUManager shareManager].selectedFilter = _demoBar.selectedFilter ;
    [FUManager shareManager].selectedFilterLevel = _demoBar.selectedFilterLevel;
}
```




### 二、在 `viewDidLoad:` 中初始化 SDK  并将  demoBar 添加到页面上

```C
    [[FUManager shareManager] loadItems];
    [self.view addSubview:self.demoBar];
```

### 三、在视频数据回调中 加入 FaceUnity  的数据处理

推流开始，在 PLPanelDelegateGenerator.m  的  generate  方法中会有视频数据的回调，修改其中的

```C
[d implementMethod:@selector(mediaStreamingSession:cameraSourceDidGetPixelBuffer:) withBlock:^CVPixelBufferRef(PLMediaStreamingSession *session, CVPixelBufferRef pixelBuffer)]
```
为以下内容：

```C
[d implementMethod:@selector(mediaStreamingSession:cameraSourceDidGetPixelBuffer:) withBlock:^CVPixelBufferRef(PLMediaStreamingSession *session, CVPixelBufferRef pixelBuffer) {
	__strong typeof(wSelf) strongSelf = wSelf;
	    
	 // 下面这一行 加入 FaceUnity 效果
	/**     -----  FaceUnity  ----     **/
	[[FUManager shareManager] renderItemsToPixelBuffer:pixelBuffer];
	/**     -----  FaceUnity  ----     **/ 
	
	if (strongSelf.needProcessVideo) {
	    size_t w = CVPixelBufferGetWidth(pixelBuffer);
	    size_t h = CVPixelBufferGetHeight(pixelBuffer);
	    size_t par = CVPixelBufferGetBytesPerRow(pixelBuffer);
	    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
	    uint8_t *pimg = CVPixelBufferGetBaseAddress(pixelBuffer);
	    for (int i = 0; i < w; i ++){
	        for (int j = 0; j < h; j++){
	            pimg[j * par + i * 4 + 1] = 255;
	        }
	    }
	    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
	}
	return pixelBuffer;
}];
```



### 四、推流结束时需要销毁道具

销毁道具需要调用以下代码

```C
[[FUManager shareManager] destoryItems];
```



####关于 FaceUnity SDK 的更多详细说明，请参看 [FULiveDemo](https://github.com/Faceunity/FULiveDemo/tree/dev)
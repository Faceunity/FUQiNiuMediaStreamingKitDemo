//
//  PLTypeDefines.h
//  PLCameraStreamingKit
//
//  Created on 15/3/26.
//  Copyright (c) 2015年 Pili Engineering. All rights reserved.
//

#ifndef PLCameraStreamingKit_PLTypeDefines_h
#define PLCameraStreamingKit_PLTypeDefines_h

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>


#pragma mark - Stream State


/*!
 @typedef    PLStreamState
 @abstract   PLStreamingSessin 的流状态。
 
 @since      v1.0.0
 */
typedef NS_ENUM(NSUInteger, PLStreamState) {
    /// PLStreamStateUnknow           未知状态，只会作为 init 的初始状态
    PLStreamStateUnknow = 0,
    /// PLStreamStateConnecting       连接中状态
    PLStreamStateConnecting,
    /// PLStreamStateConnected        已连接状态
    PLStreamStateConnected,
    /// PLStreamStateDisconnecting    断开连接中状态
    PLStreamStateDisconnecting,
    /// PLStreamStateDisconnected     已断开连接状态
    PLStreamStateDisconnected,
    /// PLStreamStateAutoReconnecting 正在等待自动重连状态
    PLStreamStateAutoReconnecting,
    /// PLStreamStateError            错误状态
    PLStreamStateError
};

#pragma mark - Network State Transition

/*!
 @typedef    PLNetworkStateTransition
 @abstract   网络切换状态变化
 */
typedef NS_ENUM(NSUInteger, PLNetworkStateTransition) {
    /// PLNetworkStateTransition                  未知转换态，作为 init 初始
    PLNetworkStateTransitionUnknown = 0,
    /// PLNetworkStateTransitionUnconnectedToWiFi 无网切换到WiFi
    PLNetworkStateTransitionUnconnectedToWiFi,
    /// PLNetworkStateTransitionUnconnectedToWWAN 无网切换到WWAN(4G, 3G, etc)
    PLNetworkStateTransitionUnconnectedToWWAN,
    /// PLNetworkStateTransitionWiFiToUnconnected WiFi切换到无网
    PLNetworkStateTransitionWiFiToUnconnected,
    /// PLNetworkStateTransitionWWANToUnconnected WWAN切换到无网
    PLNetworkStateTransitionWWANToUnconnected,
    /// PLNetworkStateTransitionWiFiToWWAN        WiFi切换至WWAN
    PLNetworkStateTransitionWiFiToWWAN,
    /// PLNetworkStateTransitionWWANToWiFi        WWAN切换至WiFi
    PLNetworkStateTransitionWWANToWiFi,
};

/*!
 @typedef    PLStreamAdaptiveQualityMode
 @abstract   自适应流质量调整模式
 */
typedef NS_ENUM(NSUInteger, PLStreamAdaptiveQualityMode) {
    /// PLStreamAdaptiveQualityModeBitratePriorAdjust   优先调整码率
    PLStreamAdaptiveQualityModeBitratePriorAdjust,
    /// PLStreamAdaptiveQualityModeFrameratePriorAdjust 优先调整帧率
    PLStreamAdaptiveQualityModeFrameratePriorAdjust,
    /// PLStreamAdaptiveQualityModeHybridAdjust         混合调整
    PLStreamAdaptiveQualityModeHybridAdjust,
};

/*!
 @typedef    PLStreamStartState
 @abstract   反馈推流操作开始的状态。
 
 @since      v2.0.0
 */
typedef NS_ENUM(NSUInteger, PLStreamStartStateFeedback) {
    /// PLStreamStartStateSuccess                       成功开始推流
    PLStreamStartStateSuccess = 0,
    /// PLStreamStartStateSessionUnknownError session   发生未知错误无法启动
    PLStreamStartStateSessionUnknownError,
    /// PLStreamStartStateSessionStillRunning session   已经在运行中，无需重复启动
    PLStreamStartStateSessionStillRunning,
    /// PLStreamStartStateStreamURLUnauthorized session 当前的 StreamURL 没有被授权
    PLStreamStartStateStreamURLUnauthorized,
    /// PLStreamStartStateSessionConnectStreamError     session 建立 socket 连接错误
    PLStreamStartStateSessionConnectStreamError,
    /// PLStreamStartStateSessionURLInvalid             session 当前传入的 pushURL 无效
    PLStreamStartStateSessionPushURLInvalid
};

#pragma mark - Log

/*!
 @typedef    PLStreamLogLevel
 @abstract   推流日志级别。
 
 @since      v2.1.0
 */
typedef NS_ENUM(NSUInteger, PLStreamLogLevel){
    // No logs
    PLStreamLogLevelOff       = 0,
    // Error logs only
    PLStreamLogLevelError,
    // Error and warning logs
    PLStreamLogLevelWarning,
    // Error, warning and info logs
    PLStreamLogLevelInfo,
    // Error, warning, info and debug logs
    PLStreamLogLevelDebug,
    // Error, warning, info, debug and verbose logs
    PLStreamLogLevelVerbose,
};


#pragma mark - Error

/*!
 @typedef    PLStreamError
 @abstract   错误状态码。

 @constant   PLStreamErrorUnknow                        未知错误
 @constant   PLStreamErrorUnknowOption                  rtmp 推流未知配置
 @constant   PLStreamErrorAccessDNSFailed               dns 无法访问
 @constant   PLStreamErrorFailedToConnectSocket         socket 连接失败
 @constant   PLStreamErrorSocksNegotiationFailed        sockket negotiation 失败
 @constant   PLStreamErrorFailedToCreateSocket          创建 socket 失败
 @constant   PLStreamErrorHandshakeFailed               握手失败
 @constant   PLStreamErrorRTMPConnectFailed             rtmp 连接失败
 @constant   PLStreamErrorSendFailed                    发送数据包失败
 @constant   PLStreamErrorServerRequestedClose          被服务端关闭
 @constant   PLStreamErrorNetStreamFailed               NetStream 失败
 @constant   PLStreamErrorNetStreamPlayFailed           NetStreamPlay 失败
 @constant   PLStreamErrorNetStreamPlayStreamNotFound   NetStreamPlay 为找到对应的流
 @constant   PLStreamErrorNetConnectionConnectInvalid   App 连接到无效的 rtmp 应用
 @constant   PLStreamErrorSanityFailed                  Sanity 失败
 @constant   PLStreamErrorSocketClosedByPeer            Socket 被关闭
 @constant   PLStreamErrorRTMPConnectStreamFailed       rtmp 连接流失败
 @constant   PLStreamErrorSocketTimeout                 socket 超时
 @constant   PLStreamErrorTLSConnectFailed              TLS 连接失败
 @constant   PLStreamErrorNoSSLOrTLSSupport             没有 SSL 或者 TLS 支持
 @constant   PLStreamErrorDNSResolveFailed              DNS 解析失败
 @constant   PLStreamErrorRTMPPublishStreamFailed       rtmp 发布失败
 
 @since      v1.0.0
 */
typedef enum {
    PLStreamErrorUnknow =	-1,
    PLStreamErrorUnknowOption = -999,
    PLStreamErrorAccessDNSFailed = -1000,
    PLStreamErrorFailedToConnectSocket = -1001,
    PLStreamErrorSocksNegotiationFailed = -1002,
    PLStreamErrorFailedToCreateSocket = -1003,
    PLStreamErrorHandshakeFailed = -1004,
    PLStreamErrorRTMPConnectFailed = -1005,
    PLStreamErrorSendFailed = -1006,
    PLStreamErrorServerRequestedClose = -1007,
    PLStreamErrorNetStreamFailed = -1008,
    PLStreamErrorNetStreamPlayFailed = -1009,
    PLStreamErrorNetStreamPlayStreamNotFound = -1010,
    PLStreamErrorNetConnectionConnectInvalidApp = -1011,
    PLStreamErrorSanityFailed = -1012,
    PLStreamErrorSocketClosedByPeer = -1013,
    PLStreamErrorRTMPConnectStreamFailed = -1014,
    PLStreamErrorSocketTimeout = -1015,
    PLStreamErrorRTMPPublishStreamFailed = -1016,
    
    // SSL errors
    PLStreamErrorTLSConnectFailed = -1200,
    PLStreamErrorNoSSLOrTLSSupport = -1201,
    
    // DNS error
    PLStreamErrorDNSResolveFailed = -1300,
    
    // reconnect error
    PLStreamErrorReconnectFailed = -1400,
    
    /*!
     @abstract 正在采集的时候被音频事件打断但重启失败
     */
    PLCameraErroRestartAudioFailed = -1500,
    /*!
     @abstract 正在采集的时候音频服务重启尝试重连但是没有成功
     */
    PLCameraErroTryReconnectFailed = -1501,
    
    // Authorization error
    PLStreamErrorAuthenticationFailed = -1600
} PLStreamError;

#pragma mark - Video Streaming Quality

/*!
 @constant   kPLVideoStreamingQualityLow1
 @abstract   视频编码推流质量 low 1。

 @discussion 具体参数 videoSize: 272x480, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 128Kbps。
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityLow1;

/*!
 @constant   kPLVideoStreamingQualityLow1
 @abstract   视频编码推流质量 low 2。

 @discussion 具体参数 videoSize: 272x480, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 256Kbps。
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityLow2;

/*!
 @constant   kPLVideoStreamingQualityLow3
 @abstract   视频编码推流质量 low 3。

 @discussion 具体参数 videoSize: 272x480, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264HighAutoLevel, video bitrate: 512Kbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityLow3;

/*!
 @constant   kPLVideoStreamingQualityMedium1
 @abstract   视频编码推流质量 medium 1。
 
 @discussion 具体参数 videoSize: 368x640, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264HighAutoLevel, video bitrate: 512Kbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityMedium1;

/*!
 @constant   kPLVideoStreamingQualityMedium2
 @abstract   视频编码推流质量 medium 2。

 @discussion 具体参数 videoSize: 368x640, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 768Kbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityMedium2;

/*!
 @constant   kPLVideoStreamingQualityMedium3
 @abstract   视频编码推流质量 medium 3。

 @discussion 具体参数 videoSize: 368x640, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 1Mbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityMedium3;

/*!
 @constant   kPLVideoStreamingQualityHigh1
 @abstract   视频编码推流质量 high 1。

 @discussion 具体参数 videoSize: 720x1280, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 1Mbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityHigh1;

/*!
 @constant   kPLVideoStreamingQualityHigh2
 @abstract   视频编码推流质量 high 2。

 @discussion 具体参数 videoSize: 720x1280, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 1.25Mbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityHigh2;

/*!
 @constant   kPLVideoStreamingQualityHigh3
 @abstract   视频编码推流质量 high 3。

 @discussion 具体参数 videoSize: 720x1280, expectedSourceVideoFrameRate: 24, videoMaxKeyframeInterval: 72, profile level: AVVideoProfileLevelH264BaselineAutoLevel, video bitrate: 1.5Mbps
 
 @since      v1.0.0
 */
extern NSString *kPLVideoStreamingQualityHigh3;

#pragma mark - Audio Streaming Quality

/*!
 @constant   kPLAudioStreamingQualityHigh1
 @abstract   音频编码推流质量 high 1。

 @discussion 具体参数 audio bitrate: 64Kbps。
 
 @since      v1.0.0
 */
extern NSString *kPLAudioStreamingQualityHigh1;

/*!
 @constant   kPLAudioStreamingQualityHigh2
 @abstract   音频编码推流质量 high 2。

 @discussion 具体参数 audio bitrate: 96Kbps。
 
 @since      v1.0.0
 */
extern NSString *kPLAudioStreamingQualityHigh2;

/*!
 @constant   kPLAudioStreamingQualityHigh3
 @abstract   音频编码推流质量 high 3。
 
 @discussion 具体参数 audio bitrate: 128Kbps。
 
 @since      v1.0.0
 */
extern NSString *kPLAudioStreamingQualityHigh3;

// post with userinfo @{@"state": @(state)}. always posted via MainQueue.
extern NSString *PLStreamStateDidChangeNotification;
extern NSString *PLCameraAuthorizationStatusDidGetNotificaiton;
extern NSString *PLMicrophoneAuthorizationStatusDidGetNotificaiton;

extern NSString *PLCameraDidStartRunningNotificaiton;
extern NSString *PLMicrophoneDidStartRunningNotificaiton;
extern NSString *PLAudioComponentFailedToCreateNotification;

/*!
 @typedef    PLH264EncoderType
 @abstract   H.264 编码器类型
 
 @constant   PLH264EncoderType_AVFoundation  采用 AVFoundation 进行编码
 @constant   PLH264EncoderType_VideoToolbox  采用 VideoToolbox 进行编码，只在 iOS 8 及以上支持，iOS 8 以下系统版本会自动回退为 PLH264EncoderType_AVFoundation 编码器
 */
typedef NS_ENUM(NSUInteger, PLH264EncoderType) {
    PLH264EncoderType_AVFoundation,    // AVFoundation 编码器
    PLH264EncoderType_VideoToolbox     // iOS 8 及以上系统版本可用 VideoToolbox 编码器，编码效率更优
};

/*!
  @abstract 音频编码模式
 */
typedef NS_ENUM(NSUInteger, PLAACEncoderType) {
    /*!
     @abstract iOS AAC（硬编）
     */
    PLAACEncoderType_iOS_AAC,
    /*!
     @abstract fdk-aac AAC
     */
    PLAACEncoderType_fdk_AAC_LC,
    /*!
     @abstract fdk-aac HE-AAC
     */
    PLAACEncoderType_fdk_AAC__HE_BSR
    
};

#pragma mark - Audio SampleRate

/*!
 @typedef    PLStreamingAudioSampleRate
 @abstract   音频编码采样率。
 
 @constant   PLStreamingAudioSampleRate_48000Hz 48000Hz 音频编码采样率
 @constant   PLStreamingAudioSampleRate_44100Hz 44100Hz 音频编码采样率
 @constant   PLStreamingAudioSampleRate_22050Hz 22050Hz 音频编码采样率
 @constant   PLStreamingAudioSampleRate_11025Hz 11025Hz 音频编码采样率
 
 @since      v1.0.0
 */
typedef NS_ENUM(NSUInteger, PLStreamingAudioSampleRate) {
    PLStreamingAudioSampleRate_48000Hz = 48000,
    PLStreamingAudioSampleRate_44100Hz = 44100,
    PLStreamingAudioSampleRate_22050Hz = 22050,
    PLStreamingAudioSampleRate_11025Hz = 11025,
};

#pragma mark - Audio BitRate

/*!
 @typedef    PLStreamingAudioBitRate
 @abstract   音频编码码率。
 
 @constant   PLStreamingAudioBitRate_64Kbps  64Kbps 音频码率
 @constant   PLStreamingAudioBitRate_96Kbps  96Kbps 音频码率
 @constant   PLStreamingAudioBitRate_128Kbps 128Kbps 音频码率

 @since      v1.0.0
 */
typedef enum {
    PLStreamingAudioBitRate_64Kbps = 64000,
    PLStreamingAudioBitRate_96Kbps = 96000,
    PLStreamingAudioBitRate_128Kbps = 128000,
} PLStreamingAudioBitRate;

/*!
 @typedef    PLAudioStreamEndian
 
 @abstract   PLAudioStreamEndian 音频流如何处理大小端。
 
 @since   @v1.2.5
 */
typedef NS_ENUM(NSUInteger, PLAudioStreamEndian) {
    /// PLAudioStreamEndian_Auto         根据 CMSampleBufferRef 的描述决定该以大端还是小端来处理
    PLAudioStreamEndian_Auto = 0,
    /// PLAudioStreamEndian_BigEndian    显式声明音频流为大端
    PLAudioStreamEndian_BigEndian = 1,
    /// PLAudioStreamEndian_LittleEndian 显式声明音频流为小端
    PLAudioStreamEndian_LittleEndian = 2
};

#pragma mark - Audio Channel

/*!
 @constant   kPLAudioChannelDefault
 @abstract   默认音频输入流
 
 @since      v1.2.5
 */
extern const NSString *kPLAudioChannelDefault;

/*!
 @constant   kPLAudioChannelApp
 @abstract   来自ReplayKit Live的Audio App音频流
 
 @since      v1.2.5
 */
extern const NSString *kPLAudioChannelApp;

/*!
 @constant   kPLAudioChannelMic
 @abstract   来自ReplayKit Live的Audio Mic音频流
 
 @since      v1.2.5
 */
extern const NSString *kPLAudioChannelMic;

/*!
 @typedef    PLAuthorizationStatus
 @abstract   设备授权状态。
 */
typedef NS_ENUM(NSUInteger, PLAuthorizationStatus) {
    /// 还没有确定是否授权
    PLAuthorizationStatusNotDetermined = 0,
    /// 设备受限，一般在家长模式下设备会受限
    PLAuthorizationStatusRestricted,
    /// 拒绝授权
    PLAuthorizationStatusDenied,
    /// 已授权
    PLAuthorizationStatusAuthorized
};

/*!
 @typedef    PLAuthenticationResult
 @abstract   SDK 授权状态查询。
 @since      v3.0.0
 */
typedef enum {
    // 还没有确定是否授权
    PLAuthenticationResultNotDetermined = 0,
    // 未授权
    PLAuthenticationResultDenied,
    // 已成功
    PLAuthenticationResultAuthorized
} PLAuthenticationResult;

/*!
 @typedef    PLVideoFillModeType
 @abstract   画面填充方式
 */
typedef enum {
    /*!
     @abstract Stretch to fill the full view, which may distort the image outside of its normal aspect ratio
     */
    PLVideoFillModeStretch,
    
    /*!
     @abstract Maintains the aspect ratio of the source image, adding bars of the specified background color
     */
    PLVideoFillModePreserveAspectRatio,
    
    /*!
     @abstract Maintains the aspect ratio of the source image, zooming in on its center to fill the view
     */
    PLVideoFillModePreserveAspectRatioAndFill
} PLVideoFillModeType;

/*!
 @abstract 方向的旋转类型
 
 @warning 以顺时针为基准
 
 @since v2.3.4
 */
typedef NS_ENUM(NSUInteger, PLRotateModeType) {
    PLRotateModeNone = 0, /// 无效果
    PLRotateModeDegree90, /// 顺时针旋转 90 度，竖屏变横屏或横屏变竖屏
    PLRotateModeDegree180, /// 倒立效果
    PLRotateModeDegree270, ///顺时针旋转 270 度，竖屏变横屏或横屏变竖屏
    PLRotateModeFlipVertical, /// 垂直翻转，倒影效果
    PLRotateModeFlipHorizonal /// 水平翻转，镜像效果
};

/*!
 @typedef    ConnectionChangeActionCallback
 @abstract   网络切换用户回调
 */
typedef BOOL(^ConnectionChangeActionCallback)(PLNetworkStateTransition transition);

/*!
 @typedef    ConnectionInterruptionHandler
 @abstract   推流断开用户回调
 */
typedef BOOL(^ConnectionInterruptionHandler)(NSError *error);

/*!
 @typedef    PLAudioEffectConfigurationType
 @abstract   音效配置类型
 */
typedef enum {
    /*!
     @abstract 由 PLMediaStreamingKit 提供的预设的音效配置
     */
    PLAudioEffectConfigurationType_Preset = 1,
    /*!
     @abstract 用户自定义音效配置
     */
    PLAudioEffectConfigurationType_Custom = 2
} PLAudioEffectConfigurationType;

/*!
 @typedef    PLAudioPlayerFileError
 @abstract   音频播放文件错误类型
 */
typedef enum {
    PLAudioPlayerFileError_FileNotExist,
    PLAudioPlayerFileError_FileOpenFail,
    PLAudioPlayerFileError_FileReadingFail
} PLAudioPlayerFileError;

/*!
 @abstract 对音频数据进行处理的回调
 */
typedef void (^PLAudioEffectCustomConfigurationBlock)(void *inRefCon,
                                                      AudioUnitRenderActionFlags *ioActionFlags,
                                                      const AudioTimeStamp *inTimeStamp,
                                                      UInt32 inBusNumber,
                                                      UInt32 inNumberFrames,
                                                      AudioBufferList *ioData);

/*!
 @abstract 音频开始被打断的回调
 */
typedef void (^PLAudioSessionDidBeginInterruptionCallback)();

/*!
 @abstract 结束音频被打断的回调
 */
typedef void (^PLAudioSessionDidEndInterruptionCallback)();

/*!
 @abstract 对截图数据进行处理的回调
 
 @since    v2.2.0
 */
typedef void (^PLStreamScreenshotHandler)(UIImage * _Nullable image);

#endif



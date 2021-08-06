//
//  PLViewController.m
//  PLMediaStreamingKitDemo
//
//  Created by hxiongan on 2018/3/12.
//  Copyright © 2018年 0dayZh. All rights reserved.
//

#import "PLViewController.h"
#import "PLMainViewController.h"

@interface PLViewController ()

/// 房间号
@property(nonatomic, strong) UITextField *roomIdTF;
@property(nonatomic, assign) BOOL isuseFU;

@end

@implementation PLViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.title = @"设置房间号";
    self.view.backgroundColor = [UIColor whiteColor];
    UITextField *roomIdTF = [[UITextField alloc] initWithFrame:CGRectMake(80, 188, self.view.frame.size.width - 160, 44)];
    roomIdTF.placeholder = @"请输入房间号";
    roomIdTF.backgroundColor = [UIColor orangeColor];
    roomIdTF.keyboardType = UIKeyboardTypeNumberPad;
    roomIdTF.layer.cornerRadius = 4;
    [self.view addSubview:roomIdTF];
    self.roomIdTF = roomIdTF;
    
    UIButton *fuBtn = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 28, 28)];
    fuBtn.userInteractionEnabled = NO;
    fuBtn.enabled = NO;
    [fuBtn setTitle:@"FU开关" forState:(UIControlStateNormal)];
    [fuBtn setTitleColor:[UIColor blackColor] forState:(UIControlStateNormal)];
    fuBtn.titleLabel.font = [UIFont systemFontOfSize:18];
    
    UISwitch *fuswitch = [[UISwitch alloc] initWithFrame:CGRectMake(0, 0, 28, 28)];
    [fuswitch addTarget:self action:@selector(selectedFUChanged:) forControlEvents:(UIControlEventValueChanged)];
    [fuswitch setOn:YES];
    
    self.navigationItem.leftBarButtonItems = @[[[UIBarButtonItem alloc] initWithCustomView:fuBtn],[[UIBarButtonItem alloc] initWithCustomView:fuswitch]];
    
    // 默认YES
    self.isuseFU = YES;
    
    UIButton *startBtn = [[UIButton alloc] initWithFrame:CGRectMake((self.view.frame.size.width - 120) / 2.0, 360, 120, 44)];
    [startBtn setTitle:@"开始推流" forState:(UIControlStateNormal)];
    startBtn.backgroundColor = [UIColor orangeColor];
    startBtn.layer.cornerRadius = 8;
    [startBtn addTarget:self action:@selector(startBtnClick) forControlEvents:(UIControlEventTouchUpInside)];
    [self.view addSubview:startBtn];
    
}

- (void)selectedFUChanged:(UISwitch *)sender{
    
    self.isuseFU = sender.isOn;
}

/// 开始推流事件点击
- (void)startBtnClick{
    
    if (self.roomIdTF.text.length == 0) {
        return;
    }
    PLMainViewController *mainVC = [[PLMainViewController alloc] init];
    mainVC.isuseFU = self.isuseFU;
    mainVC.roomId = [self.roomIdTF.text stringByReplacingOccurrencesOfString:@" " withString:@""];
    [self.navigationController pushViewController:mainVC animated:YES];
    
}




- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
  
    
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    
    [self.view endEditing:YES];
}


@end

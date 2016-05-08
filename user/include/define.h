#ifndef __DEFINE_H__
#define __DEFINE_H__ DEFINE_H

#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int


sfr T2MOD=0XC9;


//直流电机模块
sbit MA=P1^3;
sbit MB=P1^1;
sbit PWM=P1^2;

sbit ON=P1^6;





//ad转换模块
sbit CLK=P2^0;  //时钟信号 
sbit ST=P2^1;  //启动信号 
sbit EOC=P2^5;  //转换结束信号 
sbit OE=P2^3;  //输出使能
sbit ADDCS=P2^4;  //输出使能

//光强，全局变量
extern uint light;

//为了节省空间，只好定义成一个全局变量了
extern char cCmd [30];

#endif

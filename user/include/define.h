#ifndef __DEFINE_H__
#define __DEFINE_H__ DEFINE_H

#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int


sfr T2MOD=0XC9;


//ֱ�����ģ��
sbit MA=P1^3;
sbit MB=P1^1;
sbit PWM=P1^2;

sbit ON=P1^6;





//adת��ģ��
sbit CLK=P2^0;  //ʱ���ź� 
sbit ST=P2^1;  //�����ź� 
sbit EOC=P2^5;  //ת�������ź� 
sbit OE=P2^3;  //���ʹ��
sbit ADDCS=P2^4;  //���ʹ��

//��ǿ��ȫ�ֱ���
extern uint light;

//Ϊ�˽�ʡ�ռ䣬ֻ�ö����һ��ȫ�ֱ�����
extern char cCmd [30];

#endif

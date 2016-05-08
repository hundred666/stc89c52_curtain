#include<stdio.h>
#include<reg52.h>
#include"main.h"
#include"delay.h"
#include"lux.h"
#include"esp8266.h"
#include"define.h"

//todo: 如何中断定时处理ad数据
//todo: 转圈数的控制


char cmd_phone[5],info[15];
uchar TempDat,j,flag=1,connect=0,flag_send=0;
uint light=0;



void main(){
	
	
	char cCmd [30]={0};
	Chip_Init();		//初始化单片机配置


   send_cmd("AT+RST");
    while(check_respond(AT_RST)==0);
	send_cmd("AT+CIPMUX=1");
    
  while(check_respond(AT_CIPMUX)==0);
		
		send_cmd("AT+CIPSERVER=1,8800");
    while(check_respond(AT_CIPSERVER)==0);
	
ON=0;

	while(1){
		
		
		
		j=20;
		
		if(flag==1){
				if(light>130){
		
						MA=1;
						MB=0;
						PWM=1;	 //占空比0%~100%
					}else if (light<40){
						MA=0;
						MB=1;
						PWM=1;
					}else{
						MA=0;
						MB=0;
					}

		}
		
		
		
		if(TempDat=='I'){
        cmd_phone[0]=TempDat;
			
    }
    if(cmd_phone[0]=='I'&&TempDat=='P'){
        cmd_phone[1]=TempDat;
			
    }
    if(cmd_phone[1]=='P'&&TempDat=='D'){
        cmd_phone[2]=TempDat;
			
    }
    if(TempDat==':'&&cmd_phone[2]=='D'){
        cmd_phone[3]=TempDat;
			
    }
    if(cmd_phone[3]==':'){
        //cmd_phone[4]=TempDat;
			if(TempDat=='l'){
            MA=0;
            MB=1;
            PWM=1;
        }else{
            MA=1;
            MB=0;
            PWM=1;
        }
				while(j--)
            cmd_phone[j]=0;
				//flag=0;
				
				connect=1;
			flag_send=1;
			
    }
    /*if(cmd_phone[4]!=0){
        cmd_phone[5]=TempDat;
				connect=1;
			flag_send=1;
			
    }
    if(cmd_phone[5]!=0){
        if(cmd_phone[4]=='l'){
            MA=0;
            MB=1;
            PWM=1;
        }else{
            MA=1;
            MB=0;
            PWM=1;
        }
				while(j--)
            cmd_phone[j]=0;
				flag=0;
			
    }	*/		
	}
	
}

//给adc0809输入周期信号，约为640khz
void timer0() interrupt 1{//定时器0interrupt
	CLK=~CLK;//输入时钟
}

void esp8266() interrupt 4{//串口中断
	
	
	if (RI){//串口接收完整一个字节
		TempDat = SBUF;
		
		save_data(TempDat);
		RI = 0; 
	}

}

void  timer2() interrupt 5{
	
	TF2=0;
	
	TH2=-60000/256;
  TH2=-60000%256;
	
	
	ST=0;ST=1;ST=0;
		//目前定时器中断用给串口了，只好主循环延时判断

		
	
	//light=adc();
	light=P0;
	flag=1;
	
	if(connect&&flag_send){
			sprintf(info,"lux:%d",light);
			send_cmd("AT+CIPSEND=0,10");
			send_cmd(info);
		connect=0;
		flag_send=0;
		
	}
	
	
	
	//time_count--;
	/*if(time_count==0){
		flag=1;
		time_count=20000;
	}*/
	
	
		//发送给客户端信息
		//sprintf(cCmd,"lux:%d",light);
		//send_data(cCmd);
	
}




void Chip_Init(void){ //初始化单片机配置
	
	EA=1;//开启总中断
	ES=1;//开启串口中断
	
	//IE=0XB0;//开总中断和定时器2中断

	TMOD = 0X22;  //开启两个定时器，定时器0，工作模式2，读取光强；定时器1，工作模式2，读取wifi信息;自动重装

	PCON = 0X80; //8位自动重载，波特率加倍,使用串口时设置
	TH1 = 246;  //用11.0592 MHz波特率 115200
	TL1 = 0x00; 

	TR1 = 1;  //打开定时中断1

	SCON = 0X50;  //串口选择工作模式1使能接收，允许发送，允许接收

	TH0=393;//定时0，定时中断时间
	TL0=24;

	ET0=1;TR0=1;    //打开定时中断0



	ADDCS=0;
	
	
	TH2=-60000/256;
  TH2=-60000%256;

     T2CON=0;
     T2MOD=0;
     ET2=1;TR2=1;
	
	
	
	while(j--)
            cmd_phone[j]=0;
		
	
}
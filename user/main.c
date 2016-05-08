#include<stdio.h>
#include<reg52.h>
#include"main.h"
#include"delay.h"
#include"lux.h"
#include"esp8266.h"
#include"define.h"

//todo: ����ж϶�ʱ����ad����
//todo: תȦ���Ŀ���


char cmd_phone[5],info[15];
uchar TempDat,j,flag=1,connect=0,flag_send=0;
uint light=0;



void main(){
	
	
	char cCmd [30]={0};
	Chip_Init();		//��ʼ����Ƭ������


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
						PWM=1;	 //ռ�ձ�0%~100%
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

//��adc0809���������źţ�ԼΪ640khz
void timer0() interrupt 1{//��ʱ��0interrupt
	CLK=~CLK;//����ʱ��
}

void esp8266() interrupt 4{//�����ж�
	
	
	if (RI){//���ڽ�������һ���ֽ�
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
		//Ŀǰ��ʱ���ж��ø������ˣ�ֻ����ѭ����ʱ�ж�

		
	
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
	
	
		//���͸��ͻ�����Ϣ
		//sprintf(cCmd,"lux:%d",light);
		//send_data(cCmd);
	
}




void Chip_Init(void){ //��ʼ����Ƭ������
	
	EA=1;//�������ж�
	ES=1;//���������ж�
	
	//IE=0XB0;//�����жϺͶ�ʱ��2�ж�

	TMOD = 0X22;  //����������ʱ������ʱ��0������ģʽ2����ȡ��ǿ����ʱ��1������ģʽ2����ȡwifi��Ϣ;�Զ���װ

	PCON = 0X80; //8λ�Զ����أ������ʼӱ�,ʹ�ô���ʱ����
	TH1 = 246;  //��11.0592 MHz������ 115200
	TL1 = 0x00; 

	TR1 = 1;  //�򿪶�ʱ�ж�1

	SCON = 0X50;  //����ѡ����ģʽ1ʹ�ܽ��գ������ͣ��������

	TH0=393;//��ʱ0����ʱ�ж�ʱ��
	TL0=24;

	ET0=1;TR0=1;    //�򿪶�ʱ�ж�0



	ADDCS=0;
	
	
	TH2=-60000/256;
  TH2=-60000%256;

     T2CON=0;
     T2MOD=0;
     ET2=1;TR2=1;
	
	
	
	while(j--)
            cmd_phone[j]=0;
		
	
}
#include<stdio.h> 
#include"esp8266.h"
#include"define.h"
#include"lux.h"
#include"delay.h"


uint cmd;
uchar respond_data;

//char CIPMUX[]="AT+CIPMUX=1";
//char SERVER[]="AT+CIPSERVER=1,8800";


void ESP8266_Init(){
    
    unsigned int cmd=0;
    unsigned char respond_data=0; 
}

void print(char *string){//向esp8266发送数据
	ES=0;
	while(*string!='\0'){
        SBUF = *string; //把数据A送给SBUF缓存器中
        while(TI != 1);//判断发送标志位TI，如果发送完成，硬件会置TI标志位1
        TI = 0;  //TI清为0，以备下一次发送	
        string++;  
        	
	}
	string=NULL;
    //换行结束符
	SBUF = '\r'; 
	while(TI != 1);
    TI = 0;  	
	SBUF = '\n';
    while(TI != 1);
    TI = 0;  
	ES=1;
}

int length(char *string){
    int i=0;
    while(*(string++)!='\0')
        i++;
    return i;
}

void save_data(char buff){
				
				if(search_str("readyOKOK",buff)==1)
            respond_data=1;
					
		
				
}

/*void parse_cmd(char buff){
    if(buff=='I'){
        cmd_phone[0]=buff;
			
    }
    if(cmd_phone[0]=='I'&&buff=='P'){
        cmd_phone[1]=buff;
    }
    if(cmd_phone[1]=='P'&&buff=='D'){
        cmd_phone[2]=buff;
    }
    if(buff==':'&&cmd_phone[2]=='D'){
        cmd_phone[3]=buff;
    }
    if(cmd_phone[3]==':'){
        cmd_phone[4]=buff;
    }
    if(cmd_phone[4]!=0){
        cmd_phone[5]=buff;
    }
    if(cmd_phone[4]!=cmd_phone[5]){
        //motor(cmd_phone[4],cmd_phone[5]);
			
    }
    
}*/

int search_str(char *str,char buff){
	unsigned i=0;
	while(*(str+i)!='\0'){
      if(*(str+i)==buff)
				return 1;
			i++;
}
return 0;
		
		
}

/*----------------------分割线拿来分类用的，下面的是底层函数-------------------------------*/
void send_cmd(char *command){
	esp_delay();
	print(command);
	if(command=="AT+RST") cmd=AT_RST;
	else if(command=="AT+CWMODE=2")	 cmd=AT_CWMODE;
	else if(command=="AT+CWSAP=\"ESP8266\",\"12345678\",1,3")cmd=AT_CWSAP;
    else if(command=="AT+CIPMUX=1")cmd=AT_CIPMUX;
    else if(command=="AT+CIPSERVER=1,8800")cmd=AT_CIPSERVER;
    else cmd=AT_CIPSEND;
	data_init();
}

void data_init(){//初始化数据
    respond_data=0;
}

int check_respond(unsigned int def_cmd){
    switch(def_cmd){
        case AT_RST:
            if(respond_data==1){
							respond_data=0;
                return 1;
						}
            else
                return 0;
        case AT_CWMODE:
            if(respond_data==1){
							respond_data=0;
                return 1;
						}
            else
                return 0;
        case AT_CWSAP:
            if(respond_data==1)
                return 1;
            else
                return 0;
        case AT_CIPMUX:
            if(respond_data==1){
							respond_data=0;
                return 1;
					}
            else
                return 0;
        case AT_CIPSERVER:
            if(respond_data==1){
							respond_data=0;
                return 1;
						}
            else
                return 0;
        case AT_CIPSEND:
            if(respond_data==1){
							respond_data=0;
                return 1;
						}
            else
                return 0;
    }
		return 0;
}

void esp_delay(){
    unsigned short i=0xffff;
    while(i--);
}


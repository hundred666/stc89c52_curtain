#ifndef __ESP8266_H__
	#define __ESP8266_H__ ESP8266__H

	#include"define.h"

	#define AT_INIT 0
	#define AT_RST 1
	#define AT_CWMODE 2
	#define AT_CWSAP 3

	//���������
	#define AT_CIPMUXC 101
	#define AT_CIPMUX 102 //����ģʽ������OK
	#define AT_CIPSERVER 103//����������������OK
	#define AT_CIPSEND 104 //���������������

	#define DATA_SIZE 5
	
	

	//��������
	void save_data(char buff);
	int check_respond(unsigned int def_cmd);
	void print(char *string);
	int search_str(char * str,char buff);
	void send_cmd(char *cmd);
	void data_init();
	void esp_delay();
	void ESP8266_Init();
	int length(char *string);

#endif
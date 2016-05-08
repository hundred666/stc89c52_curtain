#include<reg52.h>
#include"lux.h"
#include"main.h"
#include"delay.h"
#include"define.h"


unsigned int adc() {  
    unsigned int value=0;
	//OE=0;
	
		//while(EOC==0);
	//OE=1;
    value=P0;
	//OE=0;
    return value;
}
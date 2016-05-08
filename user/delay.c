#include"delay.h"
#include"define.h"

void delay(uchar z){
	uchar x;
	while(z--)
		for(x=120;x>0;x--);
}
void delay_long(uchar x){
	uchar i=60000,j=600;
  while(x--)
		while(i--)
			while(j--);
		

}
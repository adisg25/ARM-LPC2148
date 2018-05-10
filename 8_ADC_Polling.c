
#include <LPC214x.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_uart(void);
void tx_uart(char );
void send_string(char *);
void delay(unsigned int);
void init_ADC(void);

int main() {
	unsigned int data;
	char str[12];
	PINSEL0 = 0x00050000;				//uart1 RXD and TXD
	PINSEL1 = (1<<28);					//for ADC0.3 (channel 3)
	init_uart();
	init_ADC();
	send_string("\n\rHello Aditya\n\r");
	
	while(1) {
		
		while((AD0DR3 & (1<<31)) == 0x00){};
			data = AD0DR3;
			data = (data>>6) & (0x3FF);
			sprintf(str,"\n\rADC = %d",data);
			send_string(str);
			delay(5000);
		
	}
}


void init_uart(void) {
	VPBDIV = 0x02;
	U1LCR = (1<<0) | (1<<1) |(1<<7);
	U1DLM = 0x00;
	U1DLL = 0xc3;
	U1LCR &= ~(1<<7);
}


void tx_uart(char data) {
	while(!(U1LSR & (1<<5)));
	U1THR = data;
}


void send_string(char *ptr) {
	while(*ptr != '\0') {
		tx_uart(*ptr);
		ptr++;
	}
}


void init_ADC(void) {
	AD0CR = 0x00;			//reset the ADC
	AD0CR |= (1<<3) | (1<<16) | (1<<21) | (1<<10) | (1<<9) |(1<<8);
}


void delay(unsigned int time) {
	for(int i=0; i<time; i++)
		for(int j=0; j<time; j++);
}

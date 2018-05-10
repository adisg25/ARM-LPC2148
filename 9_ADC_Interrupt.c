#include <LPC214x.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_uart(void);
void tx_uart(char );
void send_string(char *);
void adc_intr_init(void);
void intr_init(void);
void adc_ISR(void) __irq;


int main() {
	init_uart();
	intr_init();
	adc_intr_init();
	
	while(1) {
		for(int i=0; i<5000; i++)
		for(int j=0; j<5000; j++);
	}
}


void init_uart(void) {
	VPBDIV = 0x02;
	PINSEL0 = 0x00050000;
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


void adc_intr_init(void) {
	PINSEL1 = (1<<28);
	AD0CR = 0x00;			//reset ADC
	AD0CR |= (1<<3) | (1<<16) | (1<<21) | (1<<10) | (1<<9) | (1<<8);    //last thre bit are of CLKDIV
	AD0INTEN = (1<<3);
}


void intr_init(void) {
	VICIntEnable = (1<<18);
	VICVectCntl0 = 0x20|18;
	VICVectAddr0 = (unsigned long)adc_ISR;
}


void adc_ISR(void) __irq {
	unsigned int data;
	char str[10] = {0};
	data = (AD0DR3 >> 6) & (0x3FF);
	sprintf(str,"ADC = %u",data);
	send_string(str);
	VICVectAddr = 0x00;
}
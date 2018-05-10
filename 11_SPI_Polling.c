#include <LPC214x.h>


void SPI_init();
void delay(unsigned int);
void SPI_data(unsigned int);

int main() {
	SPI_init();
	
	while(1) {
		SPI_data(0xAA);
		delay(1000);
		SPI_data(0x55);
		delay(1000);
	}
}


void SPI_init() {
	VPBDIV = 0x01;
	PINSEL0 = (1<<8) | (1<<12);
	IO0DIR |= (1<<7);
	IO0SET |= (1<<7);
	S0SPCR |= (1<<5) | (1<<6) | (1<<7);
	S0SPCCR = 0x0A;														//S0SPCCR = 0x0A;
}


void delay(unsigned int time) {
	for(int i=0;i<time;i++)
		for(int j=0;j<time;j++);
}


void SPI_data(unsigned int data) {
	IO0SET |= (1<<7);
	S0SPDR = data;
	while(!(S0SPSR & (1<<7)));
	IO0CLR |= (1<<7);
}
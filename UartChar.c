#include<lpc214x.h>

void uart_init()
{
PINSEL0=0X00050000;//to tx or rx,GPIO0.8 and GPIO0.9 are used	
U1LCR=0X00000083;//wordlenght=8bits,stopbit=0,parity=0,parityselect=0,DLAB=1(first enable then disable to us DLL)
U1DLL=0X000000C3;//PCLK=30MHz,Desired_Baudrade=9600	
//U1DLM=0X00000000	optioonal line
U1LCR=0X00000003;//now disable after using DLL
}

void transmit_char(unsigned char ch)
{
	
	while(!(U1LSR & 0X020));//in U1LSR THRE bit
	U1THR=ch;	
}

unsigned char receive()
{
while(!(U1LSR & 0X01));//in U1LSR RDR bit
	return(U1RBR);
}


int main()
{
VPBDIV=0X02;	//default freq =60Mhz its converted to 30MHz
uart_init();
while(1)
{
unsigned char element=receive();
transmit_char(element);
}
return 0;
}
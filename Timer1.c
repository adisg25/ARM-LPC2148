#include <LPC214X.H>

void timer_init();
void delay();
int main()
{
IO0DIR=0xFFFFFFFF;
VPBDIV=0x01;
timer_init();

	while(1)
	{
		IO0SET=0x80000000;
		delay();
		IO0CLR=0x80000000;
		delay();
	}
return 0;	
}

void timer_init()
{
	T1CTCR=0x00;
	T1PR=60000;
	T1TCR=0x02;
	T1MR1=1000;
}

void delay()
{
	T1MCR=(1<<5);
	T1TCR=0x02;
	T1TCR=0x01;
	while(!(T1TC==1000));
	T1TCR=0x00;
}


#include<LPC214X.H>
int flag=0;
void extInt_init()
{
	EXTINT = (1<<2);
	EXTMODE = (1<<2);
	EXTPOLAR = (1<<2);
}

void EXT_INT_ISR(void)__irq
{
	EXTINT = (1<<2);
	if(flag==0)
	{
		IO0SET|=(1<<31);
		flag =1;
	}
	else
	{
		IO0CLR|=(1<<31);
		flag = 0;
	}
	VICVectAddr=0x00;
}

void intr_init()
{
	VICVectAddr0=(unsigned long)EXT_INT_ISR;
	VICVectCntl0=0x20|16;
	VICIntEnable |= (1<<16);
}

void main()
{
	PINSEL0 = (1<<31); 
	IO0DIR |= (1<<31);
	extInt_init();
	intr_init();
	while(1)
	{
	}
}

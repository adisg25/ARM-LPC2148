#include <LPC214X.H>
void delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<3000;j++);
	}
}
void main()
{
IO0DIR=0xFFFFFFFF;
IO1DIR=0xFFFFFFFF;
	while(1)
	{

		IO0SET=0x80000000;
		delay(1000);
		IO0CLR=0x80000000;
		delay(1000);
		IO1SET=0x02000000;
		delay(1000);
		IO1CLR=0x02000000;
		delay(1000);
	}
}

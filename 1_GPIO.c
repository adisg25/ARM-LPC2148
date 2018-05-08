#include <LPC214X.H>

void delay(unsigned int);

void main()
{
	IO0DIR|=(1<<31);//LED connnected to P0.31 and direction set as output
	IO1DIR|=(1<<25);//Buzzer connected to P1.25 and direction set as output
	
	while(1)
	{
		IO0SET|=(1<<31);
		IO1SET|=(1<<25);
		delay(1000);
		IO0CLR|=(1<<31);
		IO1CLR|=(1<<25);
		delay(1000);
	}
	
	
}

void delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<3000;j++);
		
	}
}

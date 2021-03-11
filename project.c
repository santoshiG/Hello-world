#include<p18f4580.h>
#include<stdio.h>
#include<string.h>

#define lcd_port P1

sbit rs=P2^0;
sbit en=P2^1;
sbit buzzer=P2^2;

char i, rx_data[50];
char rfid[13], ch;
int count1, count2, count3;
unsigned char result[1];
	
void delay(int a)
{
	int i, j;
	for(i=0; i<a; i++)
	for(j=0; j<1000; j++);
}

void dat()
{
	rs=1;
	en=1;
	delay(5);
	en=0;
}

void lcd_data(unsigned char ch)
{
	lcd_port=ch;
	dat();
}

void cmd_data()
{
	rs=0;
	en=1;
	delay(5);
	en=0;
}

void data_cmd(unsigned char dt)
{
	lcd_port=dt;
	cmd_data();
}

void string(char *str)
{
	while(*str)
	{
		lcd_data(*str);
		str++;
	}
}

void cmd()
{
	data_cmd(0x01);
	data_cmd(0x38);
	data_cmd(0x0e);
	data_cmd(0x80);
}

void serial()
{
	TMOD=0x20;
	SCON=0x50;
	TH1=0xFD;
	TR1=1;
}

char rxdata()
{
  while(!RI);
    ch=SBUF;    
    RI=0;
    return ch;
}


void main()
{
	buzzer=1;
	serial();
	cmd();
	string("   RFID Based   ");
	data_cmd(0xc0);
	string("Attendance Systm");
	delay(400);
	while(1)
	{
		data_cmd(1);
		string("Place Your Card:");
		data_cmd(0xc0);
		for(i=0;i<=12;i++) 
    rfid[i]=rxdata();
    rfid[i]='\0';
		data_cmd(1);
		string("Your Card no. is:");
		data_cmd(0xc0);
		for(i=0; i<=12; i++)
		lcd_data(rfid[i]);
		delay(400);
		if(strncmp(rfid,"123456789012",12)==0)
		{
			count1++;
			data_cmd(1);
			string(" Attendance ");
			data_cmd(0xc0);
			string(" Registered ");
			delay(400);
			data_cmd(1);
			string(" Rahul ");
			data_cmd(0xc0);
			string("Attnd. no.: ");
			sprintf(result, "%d", count1);
			string(result);	
			delay(400);
		}	
		else if(strncmp(rfid,"234567890123",12)==0)
		{
			count2++;
			data_cmd(1);
			string(" Attendance ");
			data_cmd(0xc0);
			string(" Registered ");
			delay(400);
			data_cmd(1);
			string(" Aarti ");
			data_cmd(0xc0);
			string("Attnd. no.: ");
			sprintf(result, "%d", count2);
			string(result);
			delay(400);
		}	
		else if(strncmp(rfid,"345678901234",12)==0)
		{
			count2++;
			data_cmd(1);
			string(" Attendance ");
			data_cmd(0xc0);
			string(" Registered ");
			delay(400);
			data_cmd(1);
			string(" yogesh ");
			data_cmd(0xc0);
			string("Attnd. no.: ");
			sprintf(result, "%d", count3);
			string(result);
			delay(400);
		}
		else
		{
			data_cmd(1);
			string("Invalid Card:");
			buzzer=0;
			delay(400);
			buzzer=1;
		}
	}
}

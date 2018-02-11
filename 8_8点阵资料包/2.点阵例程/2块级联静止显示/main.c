#include "main.h"

//定义变量
unsigned char temp = 0xfe;
unsigned char KEY_NUM = 0;

unsigned char Display_word[4][4] = {

//{0x00,0x3E,0x02,0x02},/*"L",0*/
//
//{0x1C,0x22,0x22,0x1C},/*"O",1*/
//
//{0x20,0x3C,0x06,0x3C},/*"V",2*/
//
//{0x00,0x3E,0x3A,0x22},/*"E",3*/

0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,
0x1C,0x1C,0x7F,0x3E,0x1C,0x08,0x00,0x00			//箭头



};

//****************************************************
//主函数
//****************************************************
void main()
{
	unsigned char j,k;
	while(1)
	{
		temp = 0x7f;
		for(j = 0 ; j < 2 ; j++)		//显示前两个字母
		{
			for(k = 0 ; k < 4 ; k++)		//一个字母4BYTE
			{
				Send_Byte(0xff);			//列选择
				Send_Byte(0x00);		    //行数据
				Send_Byte(temp);			//列选择
				Send_Byte(Display_word[j][k]);			//行数据
				LEDARRAY_LAT = 1;					//锁存数据
				_nop_();
			
				LEDARRAY_LAT = 0;
				_nop_();
				temp = (temp>>1)|0x80;
			}
		}

		temp = 0x7f;
		for(j = 2 ; j < 4 ; j++)		//显示后两个字母
		{
			for(k = 0 ; k < 4 ; k++)		//一个字母4BYTE
			{
				Send_Byte(temp);			//列选择
				Send_Byte(Display_word[j][k]);		    //行数据
				Send_Byte(0xff);			//列选择
				Send_Byte(0x00);			//行数据
				LEDARRAY_LAT = 1;					//锁存数据
				_nop_();
			
				LEDARRAY_LAT = 0;
				_nop_();
				temp = (temp>>1)|0x80;
			}
		}
		
					
	}
}

//****************************************************
//发送一个字节数据
//****************************************************
void Send_Byte( unsigned char dat)
{
	unsigned char i;
	LEDARRAY_CLK = 0;
	_nop_();	
	LEDARRAY_LAT = 0;
	_nop_();

	for( i = 0 ; i < 8 ; i++ )
	{
		if( dat&0x01 )
		{
			LEDARRAY_DI = 1;	
		}
		else
		{
			LEDARRAY_DI = 0;
		}
		
		LEDARRAY_CLK = 1;				//上升沿发送数据
		//				_nop_();
		LEDARRAY_CLK = 0;
		//				_nop_();
				
		dat >>= 1;			
	}		
}
//****************************************************
//MS延时函数(12M晶振下测试)
//****************************************************
void Delay_ms(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}
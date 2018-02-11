#include "main.h"

//�������
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
0x1C,0x1C,0x7F,0x3E,0x1C,0x08,0x00,0x00			//��ͷ



};

//****************************************************
//������
//****************************************************
void main()
{
	unsigned char j,k;
	while(1)
	{
		temp = 0x7f;
		for(j = 0 ; j < 2 ; j++)		//��ʾǰ������ĸ
		{
			for(k = 0 ; k < 4 ; k++)		//һ����ĸ4BYTE
			{
				Send_Byte(0xff);			//��ѡ��
				Send_Byte(0x00);		    //������
				Send_Byte(temp);			//��ѡ��
				Send_Byte(Display_word[j][k]);			//������
				LEDARRAY_LAT = 1;					//��������
				_nop_();
			
				LEDARRAY_LAT = 0;
				_nop_();
				temp = (temp>>1)|0x80;
			}
		}

		temp = 0x7f;
		for(j = 2 ; j < 4 ; j++)		//��ʾ��������ĸ
		{
			for(k = 0 ; k < 4 ; k++)		//һ����ĸ4BYTE
			{
				Send_Byte(temp);			//��ѡ��
				Send_Byte(Display_word[j][k]);		    //������
				Send_Byte(0xff);			//��ѡ��
				Send_Byte(0x00);			//������
				LEDARRAY_LAT = 1;					//��������
				_nop_();
			
				LEDARRAY_LAT = 0;
				_nop_();
				temp = (temp>>1)|0x80;
			}
		}
		
					
	}
}

//****************************************************
//����һ���ֽ�����
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
		
		LEDARRAY_CLK = 1;				//�����ط�������
		//				_nop_();
		LEDARRAY_CLK = 0;
		//				_nop_();
				
		dat >>= 1;			
	}		
}
//****************************************************
//MS��ʱ����(12M�����²���)
//****************************************************
void Delay_ms(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}
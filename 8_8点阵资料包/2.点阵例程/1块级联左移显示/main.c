#include "main.h"

//�������
unsigned char temp = 0xfe;
unsigned char KEY_NUM = 0;

unsigned char Display_word[24] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x10,0x38,0x54,0x10,0x10,0x10,0x10,0x10,	//��ͷ
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,


};

//****************************************************
//������
//****************************************************
void main()
{
	unsigned int i;
	unsigned char j,k;
	while(1)
	{		
		for(j = 0 ; j < 16 ; j++)		
		{
			for(i = 0 ; i < 50 ; i++)
			{
				temp = 0x7f;
				for(k = 0 ; k < 16 ; k++)		//һ����ĸ4BYTE
				{
					Send_Byte(temp);			//��ѡ��
					Send_Byte(Display_word[j+k]);			//����
					LEDARRAY_LAT = 1;					//��������
					_nop_();
				
					LEDARRAY_LAT = 0;
					_nop_();
					temp = (temp>>1)|0x80;
				}
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
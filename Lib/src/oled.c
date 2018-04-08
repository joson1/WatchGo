#include "oled.h"


void OLED_WR_Byte(unsigned char Data,bit CD) 
{
    if(CD)
    {
        // IIC_Start();
        // IIC_WR_Byte(0x78);			//D/C#=0; R/W#=0
		// 		SCL=1;
		// 		SCL=0;
        // IIC_WR_Byte(0x40);			//write data
		// 		SCL=1;
		// 		SCL=0;
        // IIC_WR_Byte(Data);
		// 		SCL=1;
		// 		SCL=0;
        // IIC_Stop();

		OBIIC_Start();
		OBIIC_SendData(0x78);
		OBIIC_RecvACK();
		OBIIC_SendData(0x40);
		OBIIC_RecvACK();
		OBIIC_SendData(Data);
		OBIIC_RecvACK();
		OBIIC_Stop();



    }
    else
    {
        // IIC_Start();
        // IIC_WR_Byte(0x78); //salave address SA0=0
		// 		SCL=1;
		// 		SCL=0;
        // IIC_WR_Byte(0x00);
		// 		SCL=1;
		// 		SCL=0;
        // IIC_WR_Byte(Data);
		// 		SCL=1;
		// 		SCL=0;
        // IIC_Stop();
		OBIIC_Start();
		OBIIC_SendData(0x78);
		OBIIC_RecvACK();
		OBIIC_SendData(0x00);
		OBIIC_RecvACK();
		OBIIC_SendData(Data);
		OBIIC_RecvACK();
		OBIIC_Stop();
    }

}

void OLED_Set_Pos(unsigned char x,unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

void OLED_Display_ON()
{
    OLED_WR_Byte(0x8d,OLED_CMD);
    OLED_WR_Byte(0x14,OLED_CMD);
    OLED_WR_Byte(0xaf,OLED_CMD);
}

void OLED_Display_OFF()
{
    OLED_WR_Byte(0x80,OLED_CMD);
    OLED_WR_Byte(0x10,OLED_CMD);
    OLED_WR_Byte(0xae,OLED_CMD);
}

//void OLED_Clear()
//{
//    unsigned char i,n;
//    for(i=0;i<8;i++)  
//	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
//		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
//		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
//		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
//	}
//}
void OLED_Clear()
{
    unsigned char i,n;
    for(i=0;i<128;i++)  
	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
//		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
//		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<8;n++)OLED_WR_Byte(0,OLED_DATA); 
	}
}
//初始化SSD1306					    
void OLED_Init(void)
{ 	
    delay();
    OLED_WR_Byte(0xAE,OLED_CMD);//关闭显示
	
	OLED_WR_Byte(0x40,OLED_CMD);//---set low column address
	OLED_WR_Byte(0xB0,OLED_CMD);//---set high column address

	OLED_WR_Byte(0xC8,OLED_CMD);//-not offset

	OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
	OLED_WR_Byte(0xff,OLED_CMD);

	OLED_WR_Byte(0xa1,OLED_CMD);//段重定向设置

	OLED_WR_Byte(0xa6,OLED_CMD);//
	
	OLED_WR_Byte(0xa8,OLED_CMD);//设置驱动路数
	OLED_WR_Byte(0x1f,OLED_CMD);
	
	OLED_WR_Byte(0xd3,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	
	OLED_WR_Byte(0xd5,OLED_CMD);
	OLED_WR_Byte(0xf0,OLED_CMD);
	
	OLED_WR_Byte(0xd9,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	
	OLED_WR_Byte(0xda,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	
	OLED_WR_Byte(0xdb,OLED_CMD);
	OLED_WR_Byte(0x49,OLED_CMD);
	
	OLED_WR_Byte(0x8d,OLED_CMD);
	OLED_WR_Byte(0x14,OLED_CMD);
	
	OLED_WR_Byte(0x20,OLED_CMD);//
	OLED_WR_Byte(0x21,OLED_CMD);
	
	OLED_WR_Byte(0xaf,OLED_CMD);
	OLED_Clear();
}  

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char* BMP)
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(*BMP,OLED_DATA);
				BMP++;
	    }
	}
} 
//void OLED_Draw(unsigned char x,unsigned char y,unsigned int Length,unsigned int width,unsigned char* BMP)
//{
//	unsigned int i,h;
//	//OLED_Set_Pos(x,y);
//	for(i=0;i<width;i++)
//	{
//		OLED_Set_Pos(x,y+i);
//		for(h=0;h<Length;h++)
//		{
//			OLED_WR_Byte(*BMP,OLED_DATA);
//			BMP++;
//		}
//		
//	}
//}
void OLED_Draw(unsigned char x,unsigned char y,unsigned int Length,unsigned int width,unsigned char* BMP)
{
	unsigned int i,h;
	//OLED_Set_Pos(x,y);
	for(i=0;i<Length;i++)
	{
		OLED_Set_Pos(x+i,y);
		for(h=0;h<width;h++)
		{
			OLED_WR_Byte(*BMP,OLED_DATA);
			BMP++;
		}
		
	}
}

#ifndef OLED_H
#define OLED_H

#include "ONboard_IIC.h"

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define OLED_MODE 0


#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  

extern void OLED_WR_Byte(unsigned char Data,bit CD);
extern void OLED_Set_Pos(unsigned char x,unsigned char y);  
extern void OLED_Display_On(void);
extern void OLED_Display_Off(void);	   							   		    
extern void OLED_Init(void);
extern void OLED_Clear(void);
extern void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void OLED_Draw(unsigned char x,unsigned char y,unsigned int Length,unsigned int width,unsigned char* BMP);
extern void displayHRmodeIcon();


#endif

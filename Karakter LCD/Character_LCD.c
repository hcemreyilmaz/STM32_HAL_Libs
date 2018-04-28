/*
	Karakter LCD Kütüphanesi
	Hüseyin Cemre Yilmaz
	hcemreyilmaz@gmail.com
	
	Kullanim	: CubeMX ile proje olustururken 6 adet GPIO pini
							asagidaki gibi tanimlanmalidir.
							
							No.		| Pin Name| Type	| Alt. Func.	| Label
							----------------------------------------------
							xx		| Pxx			| I/O		| GPIO_Output | LCD_RS
							xx		| Pxx			| I/O		| GPIO_Output | LCD_EN
							xx		| Pxx			| I/O		| GPIO_Output | LCD_D4
							xx		| Pxx			| I/O		| GPIO_Output | LCD_D5
							xx		| Pxx			| I/O		| GPIO_Output | LCD_D6
							xx		| Pxx			| I/O		| GPIO_Output | LCD_D7
							
							Pin ve port farketmeksizin, Output olarak tanimlanan pinler
							yukaridaki gibi isimlendirilmeli ve baglanti gerektigi gibi
							yapilmalidir. 
							
							Ayrica HAL_Delay fonksiyonunun mikroSaniye cinsinden calisiyor
							olmasi gerekir. Bunun icin SystemClock_Config fonksiyonunda geçen
							
							HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000); satiri
							HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000); olarak düzeltilmelidir.
							Bu degisiklik ile birlikte, HAL_Delay fonksiyonu mikrosaniye cinsinden gecikme
							saglar. Lutfen kendi yaziliminizda gerekli degisiklikleri yapiniz.
							
							Init Örnegi:
							
							LCD_Init(_LCD_4BIT, _LCD_FONT_5x8, _LCD_2LINE);
							
							4-Bit, 5x8 Font'lu, 2 satirli display kullanilacagi belirtiliyor.
							Farkli varyasyonlara Character_LCD.h dosyasindan bakabilirsiniz.
*/

#include "stm32f1xx_hal.h"
#include "Character_LCD.h"
	
void LCD_Delay(void)
{
	//HAL_Delay(_LCD_DELAY);
	for(int i=0;i<_LCD_DELAY;++i);
}

void LCD_Cmd(char out_char)
{
	LCD_RS_GPIO_Port->BRR  = LCD_RS_Pin;
	
	LCD_EN_GPIO_Port->BRR  = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR  = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR  = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR  = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR  = LCD_D7_Pin;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->ODR |= LCD_EN_Pin;
		
	if((out_char & 0x10)>>4) LCD_D4_GPIO_Port->BSRR = LCD_D4_Pin; else LCD_D4_GPIO_Port->BSRR = (uint32_t)LCD_D4_Pin << 16;
	if((out_char & 0x20)>>5) LCD_D5_GPIO_Port->BSRR = LCD_D5_Pin; else LCD_D5_GPIO_Port->BSRR = (uint32_t)LCD_D5_Pin << 16;
	if((out_char & 0x40)>>6) LCD_D6_GPIO_Port->BSRR = LCD_D6_Pin; else LCD_D6_GPIO_Port->BSRR = (uint32_t)LCD_D6_Pin << 16;
	if((out_char & 0x80)>>7) LCD_D7_GPIO_Port->BSRR = LCD_D7_Pin; else LCD_D7_GPIO_Port->BSRR = (uint32_t)LCD_D7_Pin << 16;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->BRR = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR = LCD_D7_Pin;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->ODR |= LCD_EN_Pin;
	
	if(out_char & 0x01) LCD_D4_GPIO_Port->BSRR = LCD_D4_Pin; else LCD_D4_GPIO_Port->BSRR = (uint32_t)LCD_D4_Pin << 16;
	if((out_char & 0x02)>>1) LCD_D5_GPIO_Port->BSRR = LCD_D5_Pin; else LCD_D5_GPIO_Port->BSRR = (uint32_t)LCD_D5_Pin << 16;
	if((out_char & 0x04)>>2) LCD_D6_GPIO_Port->BSRR = LCD_D6_Pin; else LCD_D6_GPIO_Port->BSRR = (uint32_t)LCD_D6_Pin << 16;
	if((out_char & 0x08)>>3) LCD_D7_GPIO_Port->BSRR = LCD_D7_Pin; else LCD_D7_GPIO_Port->BSRR = (uint32_t)LCD_D7_Pin << 16;

	LCD_Delay();
	
	LCD_EN_GPIO_Port->BRR = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR = LCD_D7_Pin;
}

void LCD_Char_CP(char out_char)
{
	LCD_RS_GPIO_Port->ODR |= LCD_RS_Pin;
	
	LCD_EN_GPIO_Port->BRR  = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR  = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR  = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR  = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR  = LCD_D7_Pin;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->ODR |= LCD_EN_Pin;
		
	if((out_char & 0x10)>>4) LCD_D4_GPIO_Port->BSRR = LCD_D4_Pin; else LCD_D4_GPIO_Port->BSRR = (uint32_t)LCD_D4_Pin << 16;
	if((out_char & 0x20)>>5) LCD_D5_GPIO_Port->BSRR = LCD_D5_Pin; else LCD_D5_GPIO_Port->BSRR = (uint32_t)LCD_D5_Pin << 16;
	if((out_char & 0x40)>>6) LCD_D6_GPIO_Port->BSRR = LCD_D6_Pin; else LCD_D6_GPIO_Port->BSRR = (uint32_t)LCD_D6_Pin << 16;
	if((out_char & 0x80)>>7) LCD_D7_GPIO_Port->BSRR = LCD_D7_Pin; else LCD_D7_GPIO_Port->BSRR = (uint32_t)LCD_D7_Pin << 16;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->BRR = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR = LCD_D7_Pin;
	
	LCD_Delay();
	
	LCD_EN_GPIO_Port->ODR |= LCD_EN_Pin;
	
	if(out_char & 0x01) LCD_D4_GPIO_Port->BSRR = LCD_D4_Pin; else LCD_D4_GPIO_Port->BSRR = (uint32_t)LCD_D4_Pin << 16;
	if((out_char & 0x02)>>1) LCD_D5_GPIO_Port->BSRR = LCD_D5_Pin; else LCD_D5_GPIO_Port->BSRR = (uint32_t)LCD_D5_Pin << 16;
	if((out_char & 0x04)>>2) LCD_D6_GPIO_Port->BSRR = LCD_D6_Pin; else LCD_D6_GPIO_Port->BSRR = (uint32_t)LCD_D6_Pin << 16;
	if((out_char & 0x08)>>3) LCD_D7_GPIO_Port->BSRR = LCD_D7_Pin; else LCD_D7_GPIO_Port->BSRR = (uint32_t)LCD_D7_Pin << 16;

	LCD_Delay();
	
	LCD_EN_GPIO_Port->BRR = LCD_EN_Pin;
	LCD_D4_GPIO_Port->BRR = LCD_D4_Pin;
	LCD_D5_GPIO_Port->BRR = LCD_D5_Pin;
	LCD_D6_GPIO_Port->BRR = LCD_D6_Pin;
	LCD_D7_GPIO_Port->BRR = LCD_D7_Pin;
}

void LCD_Out_CP(char *out_char)
{
	while(*out_char)
	{
		LCD_Delay();
		LCD_Char_CP(*out_char++);
	}
	LCD_Delay();
}


void LCD_Init(char bits, char font, char lines)
{		
		HAL_Delay(250);
	  LCD_Cmd(_RETURN_HOME);
    HAL_Delay(50);
    LCD_Cmd(0x20 | bits | font | lines);
    HAL_Delay(50);
    LCD_Cmd(_LCD_INIT);
    HAL_Delay(50);
    LCD_Cmd(0x0E);
    HAL_Delay(50);
    LCD_Cmd(0x0C);
    HAL_Delay(50);
    LCD_Cmd(0x01);
		HAL_Delay(100);
}

void LCD_Goto(unsigned char row, unsigned char column)
{	
	if(row == 1)
	{
		LCD_Cmd(0x80 + (column - 1));
	}
	else if(row == 2)
	{
		LCD_Cmd(0xC0 + (column - 1));
	} 
}

void LCD_Char(unsigned char row, unsigned char column, char out_char)
{
	LCD_Goto(row, column);
	LCD_Char_CP(out_char);
}

void LCD_Out(unsigned char row, unsigned char column, char *out_char)
{
	LCD_Goto(row, column);
	LCD_Out_CP(out_char);
}

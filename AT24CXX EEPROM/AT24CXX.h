//#########################################################
//	
//	AT24C32 ve türevleri için EEPROM okuma ve yazma
//	fonksiyonlarini barindiran kütüphane tanimlari
//	dosyasidir.
//	
//	Adres hesaplama;
//	
//	7-bit temel adres, 1 0 1 0 A2 A1 A0 seklindedir.
//	Burada Ax'ler çipin adres pinlerinin durumlarina
//	göre deger almaktadir. Bosta iken bu degerler 0'dir.
//	
//	Bu durumda AT24CXX_Address tanimi 0x50 olmalidir.
//	A2, A1 ve A0 hepsi pull-up oldugu durumda deger 0x57
//	olacaktir.
//
//#########################################################

#include "stdint.h"
#include "stm32f1xx_hal.h"
// Tanimlamalar
#define AT24CXX_Address	0x50	//AT24CXX A0 A1 A2 pinleri Low durumda iken deger 0x50

#define AT24CXX_Address_Read	((AT24CXX_Address << 1) | 0x01)	//Adresi bir sola kaydir ve Read için 0'inci biti Lojik 1 yap.
#define AT24CXX_Address_Write	((AT24CXX_Address << 1) & 0xFE)	//Adresi bir sola kaydir ve Write için 0'inci biti Lojik 0 yap.

// Önemli! MAX degerini kullandiginiz çipe göre degistiriniz.
#define AT24CXX_MemAddr_Min	0x0000	//Hafiza adres baslangici
#define	AT24CXX_MemAddr_Max	0x0FFF	//AT24C32 için son adres
#define	AT24CXX_PageSize_Max	0x20	//32byte'lik sayfalar

#define AT24CXX_IS_PageSize(PageSize) (((PageSize) > 0) && ((PageSize) <= AT24CXX_PageSize_Max))
#define AT24CXX_IS_MemAddr(MemAddr) (((MemAddr) >= AT24CXX_MemAddr_Min) && ((MemAddr) <= AT24CXX_MemAddr_Max))
#define AT24CXX_TimeOut	1000	//Okuma ve yazma islemleri için Timeout süresi 1sn olarak belirlendi, degistirilebilir

// Fonksiyon prototipleri
uint8_t AT24CXX_EEPROM_Write_Byte(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData);
uint8_t AT24CXX_EEPROM_Read_Byte(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData);
uint8_t AT24CXX_EEPROM_Write_Seq(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData, uint16_t Size);
uint8_t AT24CXX_EEPROM_Read_Seq(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData, uint16_t Size);
uint8_t AT24CXX_EEPROM_Fill_All(I2C_HandleTypeDef *hi2c);
uint8_t AT24CXX_EEPROM_Erase_All(I2C_HandleTypeDef *hi2c);





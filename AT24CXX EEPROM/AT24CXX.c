#include "AT24CXX.h"
extern void Error_Handler(void);

uint8_t AT24CXX_EEPROM_Write_Byte(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData)
{
	assert_param(AT24CXX_IS_MemAddr(MemAddr));
	if(HAL_I2C_Mem_Write(hi2c, AT24CXX_Address_Write, MemAddr, I2C_MEMADD_SIZE_16BIT, pData, 1, AT24CXX_TimeOut) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}

uint8_t AT24CXX_EEPROM_Read_Byte(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData)
{
	assert_param(AT24CXX_IS_MemAddr(MemAddr));
	if(HAL_I2C_Mem_Read(hi2c, AT24CXX_Address_Read, MemAddr, I2C_MEMADD_SIZE_16BIT, pData, 1, AT24CXX_TimeOut) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}
uint8_t AT24CXX_EEPROM_Write_Seq(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData, uint16_t Size)
{
	assert_param(AT24CXX_IS_PageSize(Size));
	if(HAL_I2C_Mem_Write(hi2c, AT24CXX_Address_Write, MemAddr, I2C_MEMADD_SIZE_16BIT, pData, Size, AT24CXX_TimeOut) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}
uint8_t AT24CXX_EEPROM_Read_Seq(I2C_HandleTypeDef *hi2c, uint16_t MemAddr, uint8_t *pData, uint16_t Size)
{
	if(HAL_I2C_Mem_Read(hi2c, AT24CXX_Address_Read, MemAddr, I2C_MEMADD_SIZE_16BIT, pData, Size, AT24CXX_TimeOut) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}
uint8_t AT24CXX_EEPROM_Fill_All(I2C_HandleTypeDef *hi2c)
{
	int x,y;
	uint8_t Dummy[AT24CXX_PageSize_Max];
	for(x=0;x<AT24CXX_PageSize_Max;x++)
	{
		Dummy[x] = 0xFF;
	}
	y = (AT24CXX_MemAddr_Max-AT24CXX_MemAddr_Min)/AT24CXX_PageSize_Max;
	for(x=0;x<y;x++)
	{
		if(HAL_I2C_Mem_Write(hi2c, AT24CXX_Address_Write, AT24CXX_MemAddr_Min, I2C_MEMADD_SIZE_16BIT, Dummy, AT24CXX_PageSize_Max, AT24CXX_TimeOut) != HAL_OK)
		{
			Error_Handler();
		}
		HAL_Delay(20);
	}
	return HAL_OK;
}
uint8_t AT24CXX_EEPROM_Erase_All(I2C_HandleTypeDef *hi2c)
{
	int x,y;
	uint8_t Dummy[AT24CXX_PageSize_Max];
	for(x=0;x<AT24CXX_PageSize_Max;x++)
	{
		Dummy[x] = 0x00;
	}
	y = (AT24CXX_MemAddr_Max-AT24CXX_MemAddr_Min)/AT24CXX_PageSize_Max;
	for(x=0;x<y;x++)
	{
		if(HAL_I2C_Mem_Write(hi2c, AT24CXX_Address_Write, AT24CXX_MemAddr_Min, I2C_MEMADD_SIZE_16BIT, Dummy, AT24CXX_PageSize_Max, AT24CXX_TimeOut) != HAL_OK)
		{
			Error_Handler();
		}
		HAL_Delay(20);
	}
	return HAL_OK;
}

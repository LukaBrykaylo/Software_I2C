/*
 * i2c_manager.c
 *
 *  source file for implementation i2c_manager.h functions
 */

#include "i2c_manager.h"
#include "main.h"

GPIO_TypeDef *GPIO_I2C;
uint16_t SDA;
uint16_t SCL;

void I2C_Init(GPIO_TypeDef *GPIO, uint16_t SDA_pin, uint16_t SCL_pin){
	GPIO_I2C = GPIO;
	SCL = SCL_pin;
	SDA = SDA_pin;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SDA;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIO_I2C, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SCL;
    HAL_GPIO_Init(GPIO_I2C, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIO_I2C, SDA, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIO_I2C, SCL, GPIO_PIN_SET);
}

void SDA_High(void) {
    HAL_GPIO_WritePin(GPIO_I2C, SDA, GPIO_PIN_SET);
}

void SDA_Low(void) {
    HAL_GPIO_WritePin(GPIO_I2C, SDA, GPIO_PIN_RESET);
}

void SCL_High(void) {
    HAL_GPIO_WritePin(GPIO_I2C, SCL, GPIO_PIN_SET);
}

void SCL_Low(void) {
    HAL_GPIO_WritePin(GPIO_I2C, SCL, GPIO_PIN_RESET);
}

void I2C_Start(void){
    SDA_High();
    SCL_High();
    HAL_Delay(1);
    SDA_Low();
    HAL_Delay(1);
    SCL_Low();
    HAL_Delay(1);
}

void I2C_Stop(void){
    SDA_Low();
    HAL_Delay(1);
    SCL_High();
    HAL_Delay(1);
    SDA_High();
    HAL_Delay(1);
}

uint8_t I2C_WriteByte(uint8_t byte){
    for (int8_t i = 7; i >= 0; i--){
        byte & (1 << i) ? SDA_High() : SDA_Low();
        HAL_Delay(1);
        SCL_High();
        HAL_Delay(1);
        SCL_Low();
        HAL_Delay(1);
    }

    SDA_High();
    HAL_Delay(1);
    SCL_High();
    HAL_Delay(1);
    uint8_t ack = !HAL_GPIO_ReadPin(GPIO_I2C, SDA);
    SCL_Low();
    HAL_Delay(1);
    return ack;
}

uint8_t I2C_ReadByte(uint8_t ack){
    uint8_t byte = 0;

    SDA_High();
    for (int8_t i = 7; i >= 0; i--){
        SCL_High();
        HAL_Delay(1);
        if (HAL_GPIO_ReadPin(GPIO_I2C, SDA))
            byte |= (1 << i);
        SCL_Low();
        HAL_Delay(1);
    }

    ack ? SDA_Low() : SDA_High();
    HAL_Delay(1);
    SCL_High();
    HAL_Delay(1);
    SCL_Low();
    HAL_Delay(1);
    SDA_High();

    return byte;
}

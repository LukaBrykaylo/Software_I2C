/*
 * i2c_manager.c
 *
 *  source file for implementation i2c_manager.h functions
 */

#include "i2c_manager.h"
#include "main.h"

void I2C_Init(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SCL_Pin;
    HAL_GPIO_Init(SCL_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

void SDA_High(void) {
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
}

void SDA_Low(void) {
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
}

void SCL_High(void) {
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

void SCL_Low(void) {
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);
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
    uint8_t ack = !HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);
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
        if (HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin))
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

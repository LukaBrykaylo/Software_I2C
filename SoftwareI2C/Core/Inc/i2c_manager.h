/**
  ******************************************************************************
  * @file           : i2c_manager.h
  * @brief          : Header for i2c_manager.c file.
  *                   This file contains functions to use I2C
  ******************************************************************************
  */

#ifndef __I2C_MANAGER_H
#define __I2C_MANAGER_H

#include <stdint.h>

/**
 * @brief initialize I2C by setting GPIO pins
 * @return void
 */
void I2C_Init(void);

/**
 * @brief Change state of SDA/SCL pins
 * @return void
 */
void SDA_Init_High(void);
void SCL_Init_High(void);
void SDA_Init_Low(void);
void SCL_Init_Low(void);

/**
 * @brief Generates start/stop I2C condition
 * @return void
 */
void I2C_Start(void);
void I2C_Stop(void);

/**
 * @brief Writes a byte to I2C bus
 * @param byte: Byte to send
 * @return ACK value
 */
uint8_t I2C_WriteByte(uint8_t byte);

/**
 * @brief Reads a byte from I2C bus
 * @param ack: (not)send ACK after received byte
 * @return Received byte
 */
uint8_t I2C_ReadByte(uint8_t ack);

#endif /* __I2C_MANAGER_H */

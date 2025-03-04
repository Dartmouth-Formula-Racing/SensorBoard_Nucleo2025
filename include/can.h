/*Author: Sasha Ries
 * Date: 1/25/25
 * File: can.c
 * Description: defines all functions related to CAN communication
 */
#include <stm32f7xx_hal_can.h>

// Function to send input data to predefined CAN addresses
void send_can1(CAN_HandleTypeDef *can, float left_velocity, float right_velocity);
// void send_can2(float left_velocity, float right_velocity);

void send_can(CAN_HandleTypeDef *can, float left_velocity, float right_velocity, uint16_t offset);

//void Error_Handler(void);

// Function to initialize CAN communication
// void MX_CAN_Init(void);
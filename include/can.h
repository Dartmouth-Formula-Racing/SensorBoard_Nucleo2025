/*Author: Sasha Ries
 * Date: 1/25/25
 * File: can.h
 * Description: defines all functions related to CAN communication
 */
#include <stm32f7xx_hal_can.h>

// Function to send input data to predefined CAN addresses
void send_can(CAN_HandleTypeDef *can, float left_velocity, float right_velocity, uint16_t offset);
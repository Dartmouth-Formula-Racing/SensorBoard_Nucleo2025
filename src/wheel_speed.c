/*Author: Sasha Ries
 * Date: 1/25/25
 * File: can.c
 * Description: defines all functions related to wheel speed calculation
 */

#include "wheel_speed.h"
#include "main.h"

#define COUNTS_PER_REVOLUTION 2048  // Resolution of encoders

/*---------------------- Functions for wheel speed calculating ------------------------------------ */

float calculate_left_velocity(uint32_t delta_t, uint32_t count) {
    // Static variable to store previous count value between function calls
    static uint32_t last_left_count = 0;
    
    // Calculate difference in encoder counts since last measurement
    volatile int32_t count_delta = (count - last_left_count);
    
    // Take absolute value of count_delta (ensuring positive result)
    count_delta = count_delta > 0 ? count_delta : -1 * count_delta;

    last_left_count = count; // Update stored count for next function call
    
    // Convert count delta to RPM:
    volatile float left_velocity =
        ((float)count_delta / COUNTS_PER_REVOLUTION) * (1000.0 * 60.0 / delta_t);
    
    return left_velocity;
}


float calculate_right_velocity(uint32_t delta_t, uint32_t count) {
    // Static variable to store previous count value between function calls
    static uint32_t last_right_count = 0;
    
    // Calculate difference in encoder counts since last measurement
    volatile int32_t count_delta = (count - last_right_count);
    
    // Take absolute value of count_delta (ensuring positive result)
    count_delta = count_delta > 0 ? count_delta : -1 * count_delta;
    
    last_right_count = count; // Update stored count for next function call
    
    // Convert count delta to RPM:
    volatile float right_velocity =
        ((float)count_delta / COUNTS_PER_REVOLUTION) * (1000.0 * 60.0 / delta_t);
    
    return right_velocity;
}
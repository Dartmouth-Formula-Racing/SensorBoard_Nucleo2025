

#include <stdint.h>
#include "filter.h"

static float FIR_impulse_response[FILTER_LENGTH] = {};

// Raw values are b values for IIR
static float IIR_raw_impulse[FILTER_LENGTH + 1] = {0.0898, 0.3594, 0.5391, 0.3594, 0.0898};
// Filtered values are a values for IIR
static float IIR_filtered_impulse[FILTER_LENGTH] = {-3.8358, 5.5208,-3.5335, 0.8486};


/* ----------------------------------------------------------- FIR Filter ---------------------------------------------- */
void FIR_filter_init(FIR_filter* filter){
    /* Clear filter buffer */
    for (uint8_t n = 0; n < FILTER_LENGTH; n++){
        filter->buffer[n] = 0.0f;
    }

    // Reset buffer index
    filter->buffer_index = 0;

    // Clear filter output 
    filter->output = 0.0f;
}

float FIR_filter_update(FIR_filter* filter, float input){

    filter->buffer[filter->buffer_index] = input;
    filter->buffer_index++;

    if (filter->buffer_index == FILTER_LENGTH){
        filter->buffer_index = 0;
    }

    filter->output = 0.0f;
    uint8_t sumIndex = filter->buffer_index;

    for (uint8_t n = 0; n < FILTER_LENGTH; n++){
        if (sumIndex > 0){
            sumIndex--;
        }else{
            sumIndex = FILTER_LENGTH - 1;
        }

        filter->output += FIR_impulse_response[n] * filter->buffer[sumIndex];
    }
    return filter->output;
}

/* ----------------------------------------------------- IIR Filter -----------------------------------------------------*/
void IIR_filter_init(IIR_filter* filter){
    /* Clear filter buffer */
    for (uint8_t n = 0; n < FILTER_LENGTH + 1; n++){
        filter->raw[n] = 0.0f;
    }

    for (uint8_t n = 0; n < FILTER_LENGTH; n++){
        filter->filtered[n] = 0.0f;
    }

    // Reset buffer index
    filter->raw_index = 0;

    // Reset filtered index
    filter->filtered_index = 0;

    // Clear filter output
    filter->output = 0.0f;
}


float IIR_filter_update(IIR_filter* filter, float input){
    filter->raw[filter->raw_index] = input;
    filter->raw_index++;
    if (filter->raw_index == FILTER_LENGTH + 1){
        filter->raw_index = 0;
    }


    filter->filtered[filter->filtered_index] = input;
    filter->filtered_index++;
    if (filter->raw_index == FILTER_LENGTH + 1){
        filter->raw_index = 0;
    }


    filter->output = 0.0f;
    uint8_t sumIndex = filter->raw_index;
    for (uint8_t n = 0; n < FILTER_LENGTH + 1; n++){
        if (sumIndex > 0){
            sumIndex--;
        }else{
            sumIndex = FILTER_LENGTH;
        }
        filter->output += IIR_raw_impulse[n] * filter->raw[sumIndex];
    }

    sumIndex = filter->filtered_index;
    for (uint8_t n = 0; n < FILTER_LENGTH; n++){
        if (sumIndex > 0){
            sumIndex--;
        }else{
            sumIndex = FILTER_LENGTH - 1;
        }
        filter->output += IIR_filtered_impulse[n] * filter->filtered[sumIndex];
    }
    return filter->output;
}
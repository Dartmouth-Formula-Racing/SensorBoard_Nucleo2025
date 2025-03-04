

#include <stdint.h>
#define FILTER_LENGTH 4

typedef struct {
    float buffer[FILTER_LENGTH];
    uint8_t buffer_index;
    float output;
} FIR_filter;

typedef struct {
    float raw[FILTER_LENGTH+1];
    float filtered[FILTER_LENGTH];
    uint8_t raw_index;
    uint8_t filtered_index;
    float output;
} IIR_filter;


void FIR_filter_init(FIR_filter* filter);
float FIR_filter_update(FIR_filter* filter, float input);

void IIR_filter_init(IIR_filter* filter);
float IIR_filter_update(IIR_filter* filter, float input);

#ifndef MFCC_H
#define MFCC_H

#include "arm_math.h"
#include <stdint.h>

void mfcc_init(void);
void mfcc_run(int16_t *pInSignal, float32_t *pOutMfcc, uint32_t signal_len);

#endif // MFCC_H

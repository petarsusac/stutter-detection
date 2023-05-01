#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <stdint.h>
#include <stddef.h>

void preprocessing_init();
int preprocessing_copy_to_buffer(int16_t *data, size_t len);
void preprocessing_run();

#endif // PREPROCESSING_H

#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <stdint.h>
#include <stddef.h>

void processing_init();
int processing_copy_to_buffer(int16_t *data, size_t len);
void processing_run();

#endif // PREPROCESSING_H

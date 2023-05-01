#include "preprocessing.h"

#include <stdint.h>
#include <string.h>
#include "arm_math.h"

#include "ai.h"
#include "mfcc.h"

#define PREPROCESSING_BUFFER_SIZE (22000U)
#define PADDING_LENGTH (2048 + 50)

#define SILENCE_TRESHOLD (300)

static int16_t preprocessing_buffer[PREPROCESSING_BUFFER_SIZE];
static volatile size_t preprocessing_buffer_index = 0;

static size_t processed_frames = 0;
static size_t positive_frames = 0;

static inline int16_t max_abs_value(int16_t *array, size_t len)
{
	int16_t max_abs = 0;
	for (size_t i = 0; i < len; i++)
	{
		int16_t abs;
		if (array[i] < 0)
		{
			abs = -1 * array[i];
		}
		else
		{
			abs = array[i];
		}

		if (abs > max_abs)
		{
			max_abs = abs;
		}
	}

	return max_abs;
}

void preprocessing_init()
{
	mfcc_init();
	ai_init();
}

int preprocessing_copy_to_buffer(int16_t *data, size_t len)
{
	if (preprocessing_buffer_index <= PREPROCESSING_BUFFER_SIZE - len)
	{
		memcpy(&preprocessing_buffer[preprocessing_buffer_index], data, len * sizeof(int16_t));
		preprocessing_buffer_index += len;
	}
	else
	{
		// Buffer is full or frame is too big
		return -1;
	}

	return 0;
}

void preprocessing_run()
{
	// Wait until buffer is filled
	while (preprocessing_buffer_index < PREPROCESSING_BUFFER_SIZE);

	// Copy data to private buffer. This should take less than the signal acquisition interrupt period (10 ms).
	static int16_t private_samples_buffer[PREPROCESSING_BUFFER_SIZE + PADDING_LENGTH];
	memcpy(private_samples_buffer, preprocessing_buffer, PREPROCESSING_BUFFER_SIZE * sizeof(int16_t));

	// Reset public buffer index so that next frame can be written
	preprocessing_buffer_index = 0;

	// Zero-padding (to get spectrogram of length 44)
	memset(&private_samples_buffer[PREPROCESSING_BUFFER_SIZE], 0, PADDING_LENGTH * sizeof(int16_t));

	// Do not process frames that contain only silence (or background noise)
	if (max_abs_value(private_samples_buffer, PREPROCESSING_BUFFER_SIZE) > SILENCE_TRESHOLD)
	{
		// Calculate MFCC spectrogram
		float32_t mfcc_out[13*44];
		mfcc_run(private_samples_buffer, mfcc_out, PREPROCESSING_BUFFER_SIZE + PADDING_LENGTH);

		// Fill AI input buffer with values of 1st and 13th MFCC coefficient
		float nn_input[2*44];
		for (int i = 0; i < 44; i++)
		{
			// Extract 1st MFCC coef.
			nn_input[i] = mfcc_out[i];
			// EXtract 13th MFCC coef.
			nn_input[44 + i] = mfcc_out[12*44 + i];
		}
		nn_input[43] = 0; // don't ask

		// Run inference
		float nn_output = ai_inference(nn_input);

		if(nn_output > 0.5)
		{
			positive_frames++;
		}

		processed_frames++;
	}
}

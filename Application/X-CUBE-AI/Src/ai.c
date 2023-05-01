#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "prolongation_model.h"
#include "prolongation_model_data.h"

#include "stm32f7xx_hal.h"

#include "ai.h"

static ai_error ai_err;
static ai_i32 nbatch;

// Chunk of memory used to hold intermediate values for neural network
AI_ALIGNED(4) static ai_u8 activations[AI_PROLONGATION_MODEL_DATA_ACTIVATIONS_SIZE];

// Buffers used to store input and output tensors
AI_ALIGNED(4) static ai_i8 in_data[AI_PROLONGATION_MODEL_IN_1_SIZE_BYTES];
AI_ALIGNED(4) static ai_i8 out_data[AI_PROLONGATION_MODEL_OUT_1_SIZE_BYTES];

// Pointer to our model
static ai_handle prolongation_model = AI_HANDLE_NULL;

// Initialize wrapper structs that hold pointers to data and info about the
// data (tensor height, width, channels)
static ai_buffer ai_input[AI_PROLONGATION_MODEL_IN_NUM] = AI_PROLONGATION_MODEL_IN;
static ai_buffer ai_output[AI_PROLONGATION_MODEL_OUT_NUM] = AI_PROLONGATION_MODEL_OUT;

static void CRC_init()
{
	__HAL_RCC_CRC_CLK_ENABLE();
	CRC_HandleTypeDef hcrc;
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
	hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
	hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
	hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
	if (HAL_CRC_Init(&hcrc) != HAL_OK)
	{
	  while(1);
	}
}

void ai_init()
{
	CRC_init();

	// Set working memory and get weights/biases from model
	ai_network_params ai_params = {
		  AI_PROLONGATION_MODEL_DATA_WEIGHTS(ai_prolongation_model_data_weights_get()),
		  AI_PROLONGATION_MODEL_DATA_ACTIVATIONS(activations)
	};

	// Set pointers wrapper structs to our data buffers
	ai_input[0].n_batches = 1;
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].n_batches = 1;
	ai_output[0].data = AI_HANDLE_PTR(out_data);

	// Create instance of neural network
	ai_err = ai_prolongation_model_create(&prolongation_model, AI_PROLONGATION_MODEL_DATA_CONFIG);
	if (ai_err.type != AI_ERROR_NONE)
	{
	  while(1);
	}

	// Initialize neural network
	if (!ai_prolongation_model_init(prolongation_model, &ai_params))
	{
	  while(1);
	}
}

float ai_inference(float *input_data)
{
	// Fill input buffer (use test value)
	for (uint32_t i = 0; i < AI_PROLONGATION_MODEL_IN_1_SIZE; i++)
	{
	  ((ai_float *)in_data)[i] = (ai_float)input_data[i];
	}

	// Perform inference
	nbatch = ai_prolongation_model_run(prolongation_model, &ai_input[0], &ai_output[0]);
	if (nbatch != 1)
	{
	  while (1);
	}

	// Read output (predicted y) of neural network
	float y_val = ((float *)out_data)[0];

	return y_val;
}



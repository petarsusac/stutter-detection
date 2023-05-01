/**
  ******************************************************************************
  * @file    prolongation_model.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Mar 29 15:36:42 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "prolongation_model.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_prolongation_model
 
#undef AI_PROLONGATION_MODEL_MODEL_SIGNATURE
#define AI_PROLONGATION_MODEL_MODEL_SIGNATURE     "0d32269572a66380bb7ac1082a72d327"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.0.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Mar 29 15:36:42 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_PROLONGATION_MODEL_N_BATCHES
#define AI_PROLONGATION_MODEL_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array dense_5_bias_array;   /* Array #0 */
AI_STATIC ai_array dense_5_weights_array;   /* Array #1 */
AI_STATIC ai_array gru2_bias_array;   /* Array #2 */
AI_STATIC ai_array gru2_recurrent_array;   /* Array #3 */
AI_STATIC ai_array gru2_kernel_array;   /* Array #4 */
AI_STATIC ai_array gru1_bias_array;   /* Array #5 */
AI_STATIC ai_array gru1_recurrent_array;   /* Array #6 */
AI_STATIC ai_array gru1_kernel_array;   /* Array #7 */
AI_STATIC ai_array conv2d_10_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_10_weights_array;   /* Array #9 */
AI_STATIC ai_array conv2d_9_bias_array;   /* Array #10 */
AI_STATIC ai_array conv2d_9_weights_array;   /* Array #11 */
AI_STATIC ai_array input_0_output_array;   /* Array #12 */
AI_STATIC ai_array conv2d_9_output_array;   /* Array #13 */
AI_STATIC ai_array conv2d_10_output_array;   /* Array #14 */
AI_STATIC ai_array gru1_output_array;   /* Array #15 */
AI_STATIC ai_array gru2_output_array;   /* Array #16 */
AI_STATIC ai_array dense_5_output_array;   /* Array #17 */
AI_STATIC ai_array activation_15_output_array;   /* Array #18 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor dense_5_bias;   /* Tensor #0 */
AI_STATIC ai_tensor dense_5_weights;   /* Tensor #1 */
AI_STATIC ai_tensor gru2_bias;   /* Tensor #2 */
AI_STATIC ai_tensor gru2_recurrent;   /* Tensor #3 */
AI_STATIC ai_tensor gru2_kernel;   /* Tensor #4 */
AI_STATIC ai_tensor gru1_bias;   /* Tensor #5 */
AI_STATIC ai_tensor gru1_recurrent;   /* Tensor #6 */
AI_STATIC ai_tensor gru1_kernel;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_10_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_10_weights;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_9_bias;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_9_weights;   /* Tensor #11 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_9_output;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_10_output;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_10_output0;   /* Tensor #15 */
AI_STATIC ai_tensor gru1_output;   /* Tensor #16 */
AI_STATIC ai_tensor gru2_output;   /* Tensor #17 */
AI_STATIC ai_tensor dense_5_output;   /* Tensor #18 */
AI_STATIC ai_tensor activation_15_output;   /* Tensor #19 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_9_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_10_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain gru1_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain gru2_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_5_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain activation_15_chain;   /* Chain #5 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d conv2d_9_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d conv2d_10_layer; /* Layer #1 */
AI_STATIC ai_layer_gru gru1_layer; /* Layer #2 */
AI_STATIC ai_layer_gru gru2_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_5_layer; /* Layer #4 */
AI_STATIC ai_layer_nl activation_15_layer; /* Layer #5 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
    dense_5_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_5_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru2_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 96,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru2_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3072,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru2_kernel_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3072,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru1_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 96,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru1_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3072,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru1_kernel_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 3072,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_10_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_10_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 5120,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_9_bias_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_9_weights_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 160,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 88,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_9_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1280,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    conv2d_10_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 512,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru1_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 512,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    gru2_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 32,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    dense_5_output_array, AI_ARRAY_FORMAT_FLOAT,
    NULL, NULL, 1,
     AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
    activation_15_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
    NULL, NULL, 1,
     AI_STATIC)




/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  dense_5_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_5_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_5_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 1, 1, 1), AI_STRIDE_INIT(4, 4, 128, 128, 128),
  1, &dense_5_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru2_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &gru2_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru2_recurrent, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 1, 1, 96), AI_STRIDE_INIT(4, 4, 128, 128, 128),
  1, &gru2_recurrent_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru2_kernel, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 1, 1, 96), AI_STRIDE_INIT(4, 4, 128, 128, 128),
  1, &gru2_kernel_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru1_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &gru1_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru1_recurrent, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 1, 1, 96), AI_STRIDE_INIT(4, 4, 128, 128, 128),
  1, &gru1_recurrent_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru1_kernel, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 1, 1, 96), AI_STRIDE_INIT(4, 4, 128, 128, 128),
  1, &gru1_kernel_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_10_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_10_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_10_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 32, 5, 1, 32), AI_STRIDE_INIT(4, 4, 128, 640, 640),
  1, &conv2d_10_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_bias, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_9_bias_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_weights, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 5, 1, 32), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &conv2d_9_weights_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 44, 2), AI_STRIDE_INIT(4, 4, 4, 4, 176),
  1, &input_0_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 20, 2), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &conv2d_9_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_10_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 8, 2), AI_STRIDE_INIT(4, 4, 4, 128, 1024),
  1, &conv2d_10_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  conv2d_10_output0, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 16), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_10_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru1_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 16), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &gru1_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  gru2_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &gru2_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  dense_5_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &dense_5_output_array, NULL)
AI_TENSOR_OBJ_DECLARE(
  activation_15_output, AI_STATIC,
  0x0, 0x0, AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &activation_15_output_array, NULL)


/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_9_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_9_weights, &conv2d_9_bias, NULL),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_layer, 0,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &conv2d_10_layer, AI_STATIC,
  .tensors = &conv2d_9_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_9_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_10_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_10_weights, &conv2d_10_bias, NULL),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_10_layer, 2,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &gru1_layer, AI_STATIC,
  .tensors = &conv2d_10_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gru1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&conv2d_10_output0),
  AI_TENSOR_LIST_ENTRY(&gru1_output),
  AI_TENSOR_LIST_ENTRY(&gru1_kernel, &gru1_recurrent, &gru1_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gru1_layer, 5,
  GRU_TYPE,
  gru, forward_gru,
  &AI_NET_OBJ_INSTANCE, &gru2_layer, AI_STATIC,
  .tensors = &gru1_chain, 
  .n_units = 32, 
  .activation_nl = ai_math_tanh, 
  .recurrent_nl = ai_math_hard_sigmoid, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .reset_after = false, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gru2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&gru1_output),
  AI_TENSOR_LIST_ENTRY(&gru2_output),
  AI_TENSOR_LIST_ENTRY(&gru2_kernel, &gru2_recurrent, &gru2_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gru2_layer, 6,
  GRU_TYPE,
  gru, forward_gru,
  &AI_NET_OBJ_INSTANCE, &dense_5_layer, AI_STATIC,
  .tensors = &gru2_chain, 
  .n_units = 32, 
  .activation_nl = ai_math_tanh, 
  .recurrent_nl = ai_math_hard_sigmoid, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .reset_after = false, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&gru2_output),
  AI_TENSOR_LIST_ENTRY(&dense_5_output),
  AI_TENSOR_LIST_ENTRY(&dense_5_weights, &dense_5_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_5_layer, 8,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &activation_15_layer, AI_STATIC,
  .tensors = &dense_5_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  activation_15_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_ENTRY(&dense_5_output),
  AI_TENSOR_LIST_ENTRY(&activation_15_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  activation_15_layer, 9,
  NL_TYPE,
  nl, forward_sigmoid,
  &AI_NET_OBJ_INSTANCE, &activation_15_layer, AI_STATIC,
  .tensors = &activation_15_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 71428, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 6272, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_PROLONGATION_MODEL_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_PROLONGATION_MODEL_OUT_NUM, &activation_15_output),
  &conv2d_9_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool prolongation_model_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_9_output_array.data = AI_PTR(activations + 1152);
    conv2d_9_output_array.data_start = AI_PTR(activations + 1152);
    conv2d_10_output_array.data = AI_PTR(activations + 0);
    conv2d_10_output_array.data_start = AI_PTR(activations + 0);
    gru1_output_array.data = AI_PTR(activations + 4224);
    gru1_output_array.data_start = AI_PTR(activations + 4224);
    gru2_output_array.data = AI_PTR(activations + 4096);
    gru2_output_array.data_start = AI_PTR(activations + 4096);
    dense_5_output_array.data = AI_PTR(activations + 4092);
    dense_5_output_array.data_start = AI_PTR(activations + 4092);
    activation_15_output_array.data = AI_PTR(NULL);
    activation_15_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool prolongation_model_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_5_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_5_bias_array.data = AI_PTR(weights + 71424);
    dense_5_bias_array.data_start = AI_PTR(weights + 71424);
    dense_5_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_5_weights_array.data = AI_PTR(weights + 71296);
    dense_5_weights_array.data_start = AI_PTR(weights + 71296);
    gru2_bias_array.format |= AI_FMT_FLAG_CONST;
    gru2_bias_array.data = AI_PTR(weights + 70912);
    gru2_bias_array.data_start = AI_PTR(weights + 70912);
    gru2_recurrent_array.format |= AI_FMT_FLAG_CONST;
    gru2_recurrent_array.data = AI_PTR(weights + 58624);
    gru2_recurrent_array.data_start = AI_PTR(weights + 58624);
    gru2_kernel_array.format |= AI_FMT_FLAG_CONST;
    gru2_kernel_array.data = AI_PTR(weights + 46336);
    gru2_kernel_array.data_start = AI_PTR(weights + 46336);
    gru1_bias_array.format |= AI_FMT_FLAG_CONST;
    gru1_bias_array.data = AI_PTR(weights + 45952);
    gru1_bias_array.data_start = AI_PTR(weights + 45952);
    gru1_recurrent_array.format |= AI_FMT_FLAG_CONST;
    gru1_recurrent_array.data = AI_PTR(weights + 33664);
    gru1_recurrent_array.data_start = AI_PTR(weights + 33664);
    gru1_kernel_array.format |= AI_FMT_FLAG_CONST;
    gru1_kernel_array.data = AI_PTR(weights + 21376);
    gru1_kernel_array.data_start = AI_PTR(weights + 21376);
    conv2d_10_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_10_bias_array.data = AI_PTR(weights + 21248);
    conv2d_10_bias_array.data_start = AI_PTR(weights + 21248);
    conv2d_10_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_10_weights_array.data = AI_PTR(weights + 768);
    conv2d_10_weights_array.data_start = AI_PTR(weights + 768);
    conv2d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_bias_array.data = AI_PTR(weights + 640);
    conv2d_9_bias_array.data_start = AI_PTR(weights + 640);
    conv2d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_weights_array.data = AI_PTR(weights + 0);
    conv2d_9_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_prolongation_model_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_PROLONGATION_MODEL_MODEL_NAME,
      .model_signature   = AI_PROLONGATION_MODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 288874,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_prolongation_model_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_prolongation_model_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_prolongation_model_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_prolongation_model_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= prolongation_model_configure_weights(net_ctx, &params->params);
  ok &= prolongation_model_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_prolongation_model_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_prolongation_model_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_PROLONGATION_MODEL_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME


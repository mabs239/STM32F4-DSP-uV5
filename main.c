/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
//#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "HelperFunctions.h"
#include <math.h>
#define ARM_MATH_CM4
#include "arm_math.h"

/*
//DSP dot product
float srcA_buf_f32[3] ={-4, -6, 1,};
float srcB_buf_f32[3] ={7, 1, 3,};
float32_t multOutput[3]; 
arm_status status;  

int main (void) {
  double X[] = {.7,0.7};
	svmPredict(X);
	arm_mult_f32(srcA_buf_f32, srcB_buf_f32, multOutput, 3);
	printf("%f, %f, %f", multOutput[0],multOutput[1],multOutput[2]);
}
*/


//#define PI 3.14159265358979323846
#include "arm_math.h"
#include "arm_const_structs.h"
#define TEST_LENGTH_SAMPLES 2048
/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
//extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
//static float32_t testOutput[TEST_LENGTH_SAMPLES/2];

float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES/2];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
uint32_t refIndex = 213, testIndex = 0;

int32_t main(void)
{
  arm_status status;
	float32_t maxValue;
	int idx;
	double angle;
	for(idx = 0; idx < TEST_LENGTH_SAMPLES; idx++){ //Test Input
		angle = (double)idx/TEST_LENGTH_SAMPLES * 2*PI;
		testInput_f32_10khz[idx] = arm_sin_f32 (angle*10);
		//printf("\n i=%i,val= %f   ", idx, testInput_f32_10khz[idx] );
	}
	
	
  status = ARM_MATH_SUCCESS;
  arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput_f32_10khz, ifftFlag, doBitReverse);  /* Process the data through the CFFT/CIFFT module */
  arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);/* Process the data through the Complex Magnitude Module for calculating the magnitude at each bin */
  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);/* Calculates maxValue and returns corresponding BIN value */
	
	for(idx = 0; idx < 1023; idx++){
		printf("\n %i %f",idx,testOutput[idx]);
	}
	
	printf("\n Status = %i, MaxIndex = %i, MaxVal=%f",status, testIndex,maxValue);
	
  if(testIndex !=  refIndex)
  {
    status = ARM_MATH_TEST_FAILURE;
  }
	

  /* ----------------------------------------------------------------------
  ** Loop here if the signals fail the PASS check.
  ** This denotes a test failure
  ** ------------------------------------------------------------------- */
  if( status != ARM_MATH_SUCCESS)
  {
    while(1);
  }
  while(1);                             /* main function does not return */
}

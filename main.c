/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
#define osObjectsPublic                     // define objects in main module
//#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "HelperFunctions.h"
#include <math.h>


//---------------------FFT defines-------------------
#define ARM_MATH_CM4
#include "arm_math.h"
#include "arm_const_structs.h"
#define TEST_LENGTH_SAMPLES 2048
float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput[TEST_LENGTH_SAMPLES];
//static float32_t testOutput[TEST_LENGTH_SAMPLES/2];
static float32_t temp[TEST_LENGTH_SAMPLES];
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
uint32_t refIndex = 213, testIndex = 0;
//RFFT
arm_rfft_fast_instance_f32 	rffti;
//---------------------End FFT defines-------------------



int32_t main(void)
{
	//---------------------FFT demo-------------------
  arm_status status;
	int idx;
	double angle;
	for(idx = 0; idx < TEST_LENGTH_SAMPLES; idx++){ //Test Input
		angle = (double)idx/TEST_LENGTH_SAMPLES * 2*PI;
		testInput_f32_10khz[idx] = arm_sin_f32 (angle*100);
	}
	status = arm_rfft_fast_init_f32(&rffti, 2048);
	arm_rfft_fast_f32( &rffti, testInput_f32_10khz, temp, 0);
	arm_rfft_fast_f32( &rffti, temp, testOutput, 1);
	printf(" sig = [");
	for(idx = 0; idx < TEST_LENGTH_SAMPLES; idx++){
		printf(" (%i) %f",idx, testOutput[idx]);
	}
	printf("]");
	//---------------------End FFT demo-------------------
 
	while(1);                            
}

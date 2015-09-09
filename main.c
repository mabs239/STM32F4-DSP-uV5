/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
//#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include "HelperFunctions.h"

void SYSCLK168(void) {
	RCC->CFGR    =0x00000000;	
	RCC->CR     &=~0x01000000;               // PLLON=0 to turn off PLL;	
	RCC->PLLCFGR =0x24002A08;                // PLLN=168,PLLM=8,PLLP=00(/2),PLLSRC=0(HSI=f_In=16 MHz), f_VCO=336 MHz , f_Out=168 MHz;
	RCC->CFGR    =0x00000002;                // SYSCLK=2(PLL) , AHB=APBx=SYSCLK (i.e. no preScalers at all);
	RCC->CR     |=0x01000000;                // PLLON=1 to turn on PLL;
	while(!(RCC->CR & 0x02000000)) {}        // Wait until PLLRDY=1;
	while((RCC->CFGR & 0x0000000F)!=0x0A){}  // Wait until SYSCLK=PLL=168 MHz;
}
void SYSCLK16(void) {
   // Reset the RCC clock configuration to the default reset state
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;
  /* Reset CFGR register */
  RCC->CFGR = 0x00000000;
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;
  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x24003010;
  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;
	while((RCC->CFGR & 0x03)) {}        // Wait until SYSCLK=HSI=16 MHz;	
}
	

/*
void Blinky(void const *argument){
	while(1){
		GPIOD->BSRRL = (1 << 13);
		osDelay(250);
		GPIOD->BSRRH = (1 << 13);
		osDelay(250);
		printf("Allah");
	}
}
*/
	//osThreadDef(Blinky, osPriorityNormal, 1, 0);

/*
 * main: initialize and start the system
 */
int main (void) {
  double X[] = {.7,0.7};
	svmPredict(X);
	
	
	//osKernelInitialize ();                // initialize CMSIS-RTOS
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// enable the clock to GPIOD
	//GPIOD->MODER |= GPIO_MODER_MODER13_0;

  // initialize peripherals here

  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	//osThreadCreate(osThread (Blinky), NULL);
	//osKernelStart ();                         // start thread execution 
}

//HelperFunctions.c
#include <stdio.h>
#include "HelperFunctions.h"
#include "math.h"


//int f_size = 2;
//int groups = 28;

double modelX[2][28] ={{0.579000344, 0.796917226, 0.422056676, 0.237648833, 0.968937944, 0.770653925, 0.484163008 , 0.213185483	,0.219116214	,0.003703923	,0.000113883	,9.42E-05	,2.30E-06	,1.16E-06	,1.75E-07	,1.04E-08,	1.695387474,	2.271354862,	0.452291288,	0.227607391,	2.077405125,	2.313796625,	2.512395494,	2.580537307,	2.71198118,	2.506749483,	2.895398071	,2.110320158},
{0.157368421,	0.108947368,	0.104736842	,0.092105263,	0.075263158,	0.078421053,	0.076315789,	0.075263158,	0.051052632	,0.092105263,	0.05,	0.042631579	,0.045789474,	0.056315789	,0.022631579,	0.028421053,	0.058421053	,0.079473684,	0.092105263,	0.074210526,	0.134210526,	0.219473684,	0.171052632,	0.23,	0.120526316	,0.235263158,	0.118421053,	0.184736842}};
double const modelY[] = {	1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,-1,	-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1};
double modelAlphas[] = {	0.454251936	,0.321773341,	11.7139214,	7.945854578	,0.855086621,	0.447928742,	10.27969317,	5.47384088,	7.444460018,	0.473481755,	1.39E-17,	2.17E-17,	2.95E-17,	5.21E-16,	0.417961766,	0.000917648,	1.011944606	,0.644913297,	20	,20,	0.668406582,	0.631434696,	0.325245149,	0.375024182	,0.703681435,	0.309626792,	0.8806807,	0.278214418};
double modelW[] = {-10.93210935, -0.325816793};
double modelB = 0.0116;
int modelLength = 28;
/*
const int f_size = 2;
const int groups = 28;
double modelX[f_size][groups] ={{0.579000344, 0.796917226, 0.422056676, 0.237648833, 0.968937944, 0.770653925, 0.484163008 , 0.213185483	,0.219116214	,0.003703923	,0.000113883	,9.42E-05	,2.30E-06	,1.16E-06	,1.75E-07	,1.04E-08,	1.695387474,	2.271354862,	0.452291288,	0.227607391,	2.077405125,	2.313796625,	2.512395494,	2.580537307,	2.71198118,	2.506749483,	2.895398071	,2.110320158},
{0.157368421,	0.108947368,	0.104736842	,0.092105263,	0.075263158,	0.078421053,	0.076315789,	0.075263158,	0.051052632	,0.092105263,	0.05,	0.042631579	,0.045789474,	0.056315789	,0.022631579,	0.028421053,	0.058421053	,0.079473684,	0.092105263,	0.074210526,	0.134210526,	0.219473684,	0.171052632,	0.23,	0.120526316	,0.235263158,	0.118421053,	0.184736842}};
double modelY[] = {	1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,1	,-1,	-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1	,-1};
double modelAlphas[] = {	0.454251936	,0.321773341,	11.7139214,	7.945854578	,0.855086621,	0.447928742,	10.27969317,	5.47384088,	7.444460018,	0.473481755,	1.39E-17,	2.17E-17,	2.95E-17,	5.21E-16,	0.417961766,	0.000917648,	1.011944606	,0.644913297,	20	,20,	0.668406582,	0.631434696,	0.325245149,	0.375024182	,0.703681435,	0.309626792,	0.8806807,	0.278214418};
double modelW[] = {-10.93210935, -0.325816793};
double modelB = 0.0116;
int modelLength = 28;
*/


/**********************************************************************/
							/* Add code to view results in debug window														*/
							/*																																		*/
							/**********************************************************************/
							 // Add ITM Port register definitions to the source code.

				
							FILE __stdout;
							FILE __stdin;

							int fputc(int ch, FILE *f) {
								if (DEMCR & TRCENA) {
									while (ITM_Port32(0) == 0);
									ITM_Port8(0) = ch;
								}
								return(ch);
							}

							//Add a debugging trace messages using printf.
							//printf("AD value = 0x%04X\r\n", AD_value);

							/**********************************************************************/
							/* Above code is useful for debug printf function.										*/
							/**********************************************************************/



/**********************************************************************/
/* 																																		*/
/*																																		*/
/**********************************************************************/
int add239(int x, int y)
{ 
	return x+y+f_size;
}

/**********************************************************************/
/* 																																		*/
/*																																		*/
/**********************************************************************/
double gaussianKernel(double x1,double x2,double sigma)
{
	double t,d,sim;
	t = (x1 - x2);
	t = -1*t*t;
	d = 2*sigma*sigma;
	sim = exp(t/d);
	return sim;
}


/**********************************************************************/
/* 																																		*/
/*																																		*/
/**********************************************************************/
void printArray(double a[], int len)
{
	int i = 0;
	printf("\r\n");
	for(i=0;i<len;i++){
		printf(" %e ",a[i]);
	}
	printf("\r\n");
}

void printArrayF(float a[], int len)
{
	int i = 0;
	printf("\r\n");
	for(i=0;i<len;i++){
		printf(" %e ",a[i]);
	}
	printf("\r\n");
}
/**********************************************************************/
/* 																																		*/
/*																																		*/
/**********************************************************************/
void printArray2D(int m, int n,double a[3][3])
{
	int i = 0, j = 0;
	printf("\r\n");
	for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				printf(" %f ",a[i][j]);
			}
			printf("\r\n");
	}
	printf("\r\n");
}



/**********************************************************************/
/* 																																		*/
/*																																		*/
/**********************************************************************/
int svmPredict(double X[])
{
		int i = 0, j =0;
		//double X[] = {.7,0.7};
		double X1;
		double X2[groups], temp[groups];
		double p = 0;
		
		
		printf("\n Bismillah Hir Rahman Nir Raheem \n");
		for(j=0; j < f_size ; ++j)
			X1 = X1 + X[j]*X[j];
		
		
				
		p = 0;
		for(i=0; i<groups; ++i){
			temp[i] = 0;
			for(j=0; j < f_size ; ++j)
			{
				//X2 = sum(model.X.^2, 2)'
				X2[i] += modelX[j][i] * modelX[j][i];
				
				//K1 = - 2 * X * model.X'
				temp[i] += X[j] * modelX[j][i];
			}
			
			//K2 = bsxfun(@plus, X2, K1)
			temp[i] = -2 * temp[i] + X2[i];// + X1;//K3
			
			//K3 = bsxfun(@plus, X1, K2)
			temp[i] = temp[i] + X1;
			
			//K4 = model.kernelFunction(1, 0) .^ K3
			temp[i] = pow(gaussianKernel(1,0,.1), temp[i]);
			
			//K5 = bsxfun(@times, model.y', K4)
			temp[i] = modelY[i] * temp[i];
			
			//K6 = bsxfun(@times, model.alphas', K5)
			temp[i] = modelAlphas[i] * temp[i];
			
			//p = sum(K6, 2)
			p = p + temp[i];
		}
		
		printArray(temp,groups);
		printf("\n Groups = %i ", groups);
		printf("\n Decision Variable = %e ", p);
		
		if(p > 0)
			printf("\n Gunshot Detected");
		else
			printf("\n Noise Signal");
		return p;
	}

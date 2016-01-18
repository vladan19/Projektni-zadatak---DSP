#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "buffer.h"

float HPfilterCoefs[HPFILTER_ORDER] = {0.000066 ,-0.000143 ,-0.000261 ,-0.000202 ,-0.000000 ,0.000216 ,0.000296 ,0.000173 ,-0.000085 ,-0.000308 ,-0.000335 ,-0.000123 ,0.000203 ,0.000423 ,0.000363 ,0.000032 ,-0.000367 ,-0.000551 ,-0.000358 ,0.000122 ,0.000578 ,0.000674 ,0.000290 ,-0.000356 ,-0.000828 ,-0.000758 ,-0.000126 ,0.000678 ,0.001091 ,0.000763 ,-0.000160 ,-0.001080 ,-0.001327 ,-0.000643 ,0.000588 ,0.001536 ,0.001482 ,0.000352 ,-0.001158 ,-0.002000 ,-0.001492 ,0.000145 ,0.001853 ,0.002408 ,0.001290 ,-0.000871 ,-0.002627 ,-0.002676 ,-0.000810 ,0.001822 ,0.003408 ,0.002708 ,0.000000 ,-0.002970 ,-0.004100 ,-0.002405 ,0.001172 ,0.004251 ,0.004582 ,0.001668 ,-0.002714 ,-0.005570 ,-0.004714 ,-0.000407 ,0.004601 ,0.006796 ,0.004341 ,-0.001457 ,-0.006775 ,-0.007764 ,-0.003290 ,0.003990 ,0.009149 ,0.008275 ,0.001366 ,-0.007264 ,-0.011609 ,-0.008076 ,0.001689 ,0.011387 ,0.014023 ,0.006820 ,-0.006283 ,-0.016595 ,-0.016249 ,-0.003932 ,0.013235 ,0.023509 ,0.018151 ,-0.001841 ,-0.024685 ,-0.034055 ,-0.019607 ,0.014455 ,0.048614 ,0.056773 ,0.020521 ,-0.058827 ,-0.157650 ,-0.239264 ,0.729167 ,-0.239264 ,-0.157650 ,-0.058827 ,0.020521 ,0.056773 ,0.048614 ,0.014455 ,-0.019607 ,-0.034055 ,-0.024685 ,-0.001841 ,0.018151 ,0.023509 ,0.013235 ,-0.003932 ,-0.016249 ,-0.016595 ,-0.006283 ,0.006820 ,0.014023 ,0.011387 ,0.001689 ,-0.008076 ,-0.011609 ,-0.007264 ,0.001366 ,0.008275 ,0.009149 ,0.003990 ,-0.003290 ,-0.007764 ,-0.006775 ,-0.001457 ,0.004341 ,0.006796 ,0.004601 ,-0.000407 ,-0.004714 ,-0.005570 ,-0.002714 ,0.001668 ,0.004582 ,0.004251 ,0.001172 ,-0.002405 ,-0.004100 ,-0.002970 ,0.000000 ,0.002708 ,0.003408 ,0.001822 ,-0.000810 ,-0.002676 ,-0.002627 ,-0.000871 ,0.001290 ,0.002408 ,0.001853 ,0.000145 ,-0.001492 ,-0.002000 ,-0.001158 ,0.000352 ,0.001482 ,0.001536 ,0.000588 ,-0.000643 ,-0.001327 ,-0.001080 ,-0.000160 ,0.000763 ,0.001091 ,0.000678 ,-0.000126 ,-0.000758 ,-0.000828 ,-0.000356 ,0.000290 ,0.000674 ,0.000578 ,0.000122 ,-0.000358 ,-0.000551 ,-0.000367 ,0.000032 ,0.000363 ,0.000423 ,0.000203 ,-0.000123 ,-0.000335 ,-0.000308 ,-0.000085 ,0.000173 ,0.000296 ,0.000216 ,-0.000000 ,-0.000202 ,-0.000261 ,-0.000143 ,0.000066};

float LPfilterCoefs[LPFILTER_ORDER] = {0.000247 ,0.000250 ,0.000187 ,0.000070 ,-0.000072 ,-0.000204 ,-0.000290 ,-0.000303 ,-0.000233 ,-0.000090 ,0.000095 ,0.000273 ,0.000396 ,0.000420 ,0.000327 ,0.000127 ,-0.000136 ,-0.000395 ,-0.000575 ,-0.000612 ,-0.000478 ,-0.000186 ,0.000198 ,0.000577 ,0.000838 ,0.000892 ,0.000694 ,0.000270 ,-0.000286 ,-0.000829 ,-0.001201 ,-0.001272 ,-0.000985 ,-0.000381 ,0.000403 ,0.001164 ,0.001678 ,0.001770 ,0.001366 ,0.000527 ,-0.000555 ,-0.001595 ,-0.002292 ,-0.002409 ,-0.001853 ,-0.000712 ,0.000748 ,0.002144 ,0.003072 ,0.003221 ,0.002472 ,0.000948 ,-0.000993 ,-0.002842 ,-0.004065 ,-0.004255 ,-0.003261 ,-0.001249 ,0.001307 ,0.003737 ,0.005342 ,0.005590 ,0.004283 ,0.001641 ,-0.001717 ,-0.004913 ,-0.007028 ,-0.007363 ,-0.005649 ,-0.002168 ,0.002275 ,0.006523 ,0.009361 ,0.009841 ,0.007580 ,0.002922 ,-0.003082 ,-0.008890 ,-0.012842 ,-0.013603 ,-0.010568 ,-0.004114 ,0.004385 ,0.012809 ,0.018765 ,0.020200 ,0.015986 ,0.006358 ,-0.006949 ,-0.020899 ,-0.031700 ,-0.035577 ,-0.029625 ,-0.012552 ,0.014875 ,0.049786 ,0.087600 ,0.122809 ,0.149975 ,0.164760 ,0.164760 ,0.149975 ,0.122809 ,0.087600 ,0.049786 ,0.014875 ,-0.012552 ,-0.029625 ,-0.035577 ,-0.031700 ,-0.020899 ,-0.006949 ,0.006358 ,0.015986 ,0.020200 ,0.018765 ,0.012809 ,0.004385 ,-0.004114 ,-0.010568 ,-0.013603 ,-0.012842 ,-0.008890 ,-0.003082 ,0.002922 ,0.007580 ,0.009841 ,0.009361 ,0.006523 ,0.002275 ,-0.002168 ,-0.005649 ,-0.007363 ,-0.007028 ,-0.004913 ,-0.001717 ,0.001641 ,0.004283 ,0.005590 ,0.005342 ,0.003737 ,0.001307 ,-0.001249 ,-0.003261 ,-0.004255 ,-0.004065 ,-0.002842 ,-0.000993 ,0.000948 ,0.002472 ,0.003221 ,0.003072 ,0.002144 ,0.000748 ,-0.000712 ,-0.001853 ,-0.002409 ,-0.002292 ,-0.001595 ,-0.000555 ,0.000527 ,0.001366 ,0.001770 ,0.001678 ,0.001164 ,0.000403 ,-0.000381 ,-0.000985 ,-0.001272 ,-0.001201 ,-0.000829 ,-0.000286 ,0.000270 ,0.000694 ,0.000892 ,0.000838 ,0.000577 ,0.000198 ,-0.000186 ,-0.000478 ,-0.000612 ,-0.000575 ,-0.000395 ,-0.000136 ,0.000127 ,0.000327 ,0.000420 ,0.000396 ,0.000273 ,0.000095 ,-0.000090 ,-0.000233 ,-0.000303 ,-0.000290 ,-0.000204 ,-0.000072 ,0.000070 ,0.000187 ,0.000250 ,0.000247};
	
Buffer HPdelayBuff1;
Buffer HPdelayBuff2;
Buffer LPdelayBuff1;
Buffer LPdelayBuff2;
Buffer LPdelayBuff3;
Buffer LPdelayBuff4;
//float HPdelayBuff2[HPFILTER_ORDER-1] = {0};
//float LPdelayBuff1[LPFILTER_ORDER-1] = {0};
//float LPdelayBuff2[LPFILTER_ORDER-1] = {0};
//float LPdelayBuff3[LPFILTER_ORDER-1] = {0};
//float LPdelayBuff4[LPFILTER_ORDER-1] = {0};

// input and output channels
float inputCh[MAX_NUM_IN_CH][BLOCK_SIZE] = {0};
float outputCh[MAX_NUM_OUT_CH][BLOCK_SIZE] = {0};

void ReadChannels(FILE* input);
void ProcessChannels(int outputMode, float gain);
void WriteChannels(FILE* output);
void LPFilter(float* buffer, Buffer* delay);
void HPFilter(float* buffer, Buffer* delay);

float temporaryCh;


int main(int argc, char** argv)
{
	// streams
	FILE* input;
	FILE* output;

	// default params
	int enable = ENABLE;
	float gain = GAIN;
	int outputMode = OUTPUT_MODE;

	if (argc != 3 && argc!=6)
	{
		printf("Usage: model0 <input_file> <output_file> [<enable>] [<gain>] [<output_mode>]\n\n");
		return -1;
	}
	if (argc == 6)
	{
		// user can override default params
		enable = atoi(argv[3]);
		if(enable!=0 && enable!=1){
		  printf("Enable must be 0 or 1!\n");
		  return -1;
		}
		gain = atof(argv[4]);
		if(gain>0){
		  printf("Input gain must be between 0 and -Inf!\n");
		  return -1;
		}
		gain=pow((double)10, gain/20);
		char* outputMo = argv[5];
		if(strcmp(outputMo, "2_0_0")==0){
		  outputMode=0;
		}
		else if(strcmp(outputMo, "2_0_1")==0){
		  outputMode=1;
		}
		else if(strcmp(outputMo, "2_2_0")==0){
		  outputMode=2;
		}
		else if(strcmp(outputMo, "2_2_1")==0){
		  outputMode=3;
		}
		else{
		  printf("Output mode must be 2_0_0 || 2_0_1 || 2_2_0 || 2_2_1!\n");
		  return -1;
		}
	}
	
	char* inputFileName = argv[1];
	char* outputFileName = argv[2];
	
	if ((input = fopen(inputFileName, "rb")) == NULL)
	{
		printf("Error opening input file!\n");
		return -1;
	}

	if ((output = fopen(outputFileName, "wb")) == NULL)
	{
		printf("Error opening output file!\n");
		return -1;
	}


	initBuffer(&HPdelayBuff1, HPFILTER_ORDER-1);
	initBuffer(&HPdelayBuff2, HPFILTER_ORDER-1);
	initBuffer(&LPdelayBuff1, LPFILTER_ORDER-1);
	initBuffer(&LPdelayBuff2, LPFILTER_ORDER-1);
	initBuffer(&LPdelayBuff3, LPFILTER_ORDER-1);
	initBuffer(&LPdelayBuff4, LPFILTER_ORDER-1);
	while (enable)
	{
		// read 7 input channels and place them in buffers
		ReadChannels(input);

		// end of input stream reached?
		if (feof(input))
			break;
		
		// calculate 2 output channels using given configuration
		ProcessChannels(outputMode, gain);

		// write from output buffers to stream
		WriteChannels(output);
	}


	fclose(input);
	fclose(output);
	deleteBuffer(&HPdelayBuff1);
	deleteBuffer(&HPdelayBuff2);
	deleteBuffer(&LPdelayBuff1);
	deleteBuffer(&LPdelayBuff2);
	deleteBuffer(&LPdelayBuff3);
	deleteBuffer(&LPdelayBuff4);


	return 0;
}


void ReadChannels(FILE* input)
{
	short tmp;
	int i;
	int j;
	
	// read block of samples from input stream
	for (i=0; i<BLOCK_SIZE; i++)
	{
			for (j=0; j<MAX_NUM_IN_CH ; j++)
			{
				fread(&tmp, 2, 1, input);
				inputCh[j][i] = tmp / SCALE_FACTOR;
			}
	}
}

void ProcessChannels(int outputMode, float gain)
{
	int CurrOutputChMask[MAX_NUM_OUT_CH];
	int i;
	int j;


	for (j=0; j<MAX_NUM_OUT_CH; j++)
	{
		CurrOutputChMask[j] = outputChMask[outputMode][j];
	}

	for (i=0; i<BLOCK_SIZE; i++)
	{
		// apply gain to all channels
		for (j=0; j<MAX_NUM_IN_CH ; j++)
		{
			inputCh[j][i] *= gain;
		}

		// perform processing
		outputCh[LEFTSURROUND][i] = inputCh[LEFT][i];
		HPFilter(&outputCh[LEFTSURROUND][i], &HPdelayBuff1);
		
		outputCh[SUB][i] = inputCh[LEFT][i];
		LPFilter(&outputCh[SUB][i], &LPdelayBuff1);
		outputCh[SUB][i] *= minus9_4dB;
		
		outputCh[LEFT][i] = outputCh[LEFTSURROUND][i];
		LPFilter(&outputCh[LEFT][i], &LPdelayBuff2);
		outputCh[LEFT][i] *= minus3_8dB;
		outputCh[LEFT][i] += outputCh[SUB][i];
		
		outputCh[RIGHTSURROUND][i] = inputCh[RIGHT][i];
		HPFilter(&outputCh[RIGHTSURROUND][i], &HPdelayBuff2);
		
		temporaryCh = inputCh[RIGHT][i];
		LPFilter(&temporaryCh, &LPdelayBuff3);
		temporaryCh *= minus9_4dB;
		
		outputCh[RIGHT][i] = outputCh[RIGHTSURROUND][i];
		LPFilter(&outputCh[RIGHT][i], &LPdelayBuff4);
		outputCh[RIGHT][i] *= minus3_8dB;
		outputCh[RIGHT][i] += temporaryCh;

		// check if output exists
		for (j=0; j<MAX_NUM_OUT_CH; j++)
		{
			if (CurrOutputChMask[j] == 0)
				outputCh[j][i] = 0;
		}
	}
}


void WriteChannels(FILE* output)
{
	short tmp;
	int i;
	int j;
	
	// write block of samples to output stream (2 channels)
	for (i=0; i<BLOCK_SIZE; i++)
	{
		for (j=0; j<MAX_NUM_OUT_CH ; j++)
		{
			tmp = outputCh[j][i] * SCALE_FACTOR;
			fwrite(&tmp, 2, 1, output);
		}
	}
}

void LPFilter(float* sample, Buffer* delay)
{
	float temp;
	int i;
	int j;

	temp = *sample * LPfilterCoefs[0];
	
	if(!isEmpty(delay)){
	  j=delay->rear-1;
	  if(j<0){
	    j=delay->capacity-1;
	  }
	  for(i=1; j!=delay->front; )
	  {
		  temp += delay->buff[j] * LPfilterCoefs[i];
		  --j;
		  ++i;
		  if(j<0){
		    j=delay->capacity-1;
		  }
	  }
	  temp+=delay->buff[j] * LPfilterCoefs[i];
	}

	insert(delay, *sample);

	*sample = temp;
}

void HPFilter(float* sample, Buffer* delay)
{
	float temp;
	int i;
	int j;

	temp = *sample * HPfilterCoefs[0];
	
	if(!isEmpty(delay)){
	  j=delay->rear-1;
	  if(j<0){
	    j=delay->capacity-1;
	  }
	  for(i=1; j!=delay->front; )
	  {
		  temp += delay->buff[j] * HPfilterCoefs[i];
		  --j;
		  ++i;
		  if(j<0){
		    j=delay->capacity-1;
		  }
	  }
	  temp+=delay->buff[j] * HPfilterCoefs[i];
	}

	insert(delay, *sample);

	*sample = temp;
}


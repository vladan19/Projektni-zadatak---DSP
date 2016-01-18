#ifndef COMMON_H
#define COMMON_H


#define minus3_8dB	0.64565422903465551587821406812811f
#define minus9_4dB	0.33884415613920254704827359050211f
#define minus0dB             1.00000000000000000000000000000000f

// default param values
#define ENABLE			1
#define GAIN			minus0dB
#define OUTPUT_MODE		1

#define BLOCK_SIZE      16
#define MAX_NUM_OUT_CH  5
#define MAX_NUM_IN_CH   2

// index of channels
#define LEFT            0
#define RIGHT           1
#define LEFTSURROUND    2
#define RIGHTSURROUND   3
#define SUB             4

#define HPFILTER_ORDER	201
#define LPFILTER_ORDER  200

//							 L  R Ls Rs  Sub
int outputChMask[4][6] = {	{1, 1, 0, 0, 0},
							{1, 1, 0, 0, 1},
							{1, 1, 1, 1, 0},
							{1, 1, 1, 1, 1}};

// for conversion to floating point
#define SCALE_FACTOR  32768.0f


#endif
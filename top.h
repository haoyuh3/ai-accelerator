#ifndef __TOP_H__
#define __TOP_H__

#include <cmath>
#include <ap_int.h>
using namespace std;


#define C_SIM

#define FEAT_DIM 112
#define KERN_DIM 3
#define OUT_DIM 110
#define CH_IN 3
#define CH_OUT 32

typedef ap_int<32> int32;

// Prototype of top level function for C-synthesis

void conv(
		int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
		int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
		int32 output[CH_OUT][OUT_DIM][OUT_DIM]);

//template <int MAT_A_ROWS, int MAT_A_COLS, int MAT_B_ROWS, int MAT_B_COLS>
void conv3x3(
		int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
		int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
		int32 output[CH_OUT][OUT_DIM][OUT_DIM]);

#endif

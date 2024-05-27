#include "top.h"


/*
 * NOTE:
 *
 * mx is the number of rows;
 * nx is the number of cols.
 *
 * In a matmul,
 * ma = mc, nb = nc, na = mb
 */

void conv(int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
		int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
		int32 output[CH_OUT][OUT_DIM][OUT_DIM]
									)
{
	conv3x3(feature, kernel, output);
}

// solution 1
//void conv3x3(
//      int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
//	  int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
//	  int32 output[CH_OUT][OUT_DIM][OUT_DIM])
//{
////	#pragma HLS array_partition variable=kernel dim=2 cyclic factor = 3
////	#pragma HLS array_partition variable=feature dim=1 cyclic factor = 3
//	ch_out: for(int c_out = 0; c_out < CH_OUT; c_out ++) {
//		col_out: for(int x_out = 0; x_out < OUT_DIM; x_out ++) {
//			row_out: for(int y_out = 0; y_out < OUT_DIM; y_out ++) {
//				int32 acc = 0;
//				ch_in: for(int c_in = 0; c_in < CH_IN; c_in ++) {
//					row_k: for (int y_k = 0; y_k < KERN_DIM; y_k ++) {
//						col_k: for (int x_k = 0; x_k < KERN_DIM; x_k ++) {
//							acc += kernel[c_out][c_in][y_k][x_k]*feature[c_in][y_k + y_out][x_k + x_out];
//						}
//					}
//				}
//				output[c_out][y_out][x_out] = acc;
//			}
//		}
//	}
//}


//solution2
//void conv3x3(
//      int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
//	  int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
//	  int32 output[CH_OUT][OUT_DIM][OUT_DIM])
//{
//
//	#pragma HLS array_partition variable=kernel dim=1 complete
//	#pragma HLS array_partition variable=kernel dim=2 complete
//	#pragma HLS array_partition variable=kernel dim=3 complete
//	#pragma HLS array_partition variable=kernel dim=4 complete
//
//	#pragma HLS array_partition variable=feature dim=1 complete
//	#pragma HLS array_partition variable=output dim = 1 complete
//
//	row_k: for (int y_k = 0; y_k < KERN_DIM; y_k ++) {
//		col_k: for (int x_k = 0; x_k < KERN_DIM; x_k ++){
//
//			row_out: for(int y_out = 0; y_out < OUT_DIM; y_out ++){
//				col_out: for(int x_out = 0; x_out < OUT_DIM; x_out ++) {
//					#pragma HLS PIPELINE
//					ch_in: for(int c_in = 0; c_in < CH_IN; c_in ++) {
//						ch_out: for(int c_out = 0; c_out < CH_OUT; c_out ++) {
//							output[c_out][y_out][x_out] += kernel[c_out][c_in][y_k][x_k]*feature[c_in][y_k + y_out][x_k + x_out];
//						}
//					}
//				}
//
//			}
//		}
//	}
//}




//solution3
void conv3x3(
      int32 feature[CH_IN][FEAT_DIM][FEAT_DIM],
	  int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM],
	  int32 output[CH_OUT][OUT_DIM][OUT_DIM])
{

	#pragma HLS array_partition variable=kernel dim=1 complete
	#pragma HLS array_partition variable=kernel dim=2 complete
	#pragma HLS array_partition variable=kernel dim=3 complete
	#pragma HLS array_partition variable=kernel dim=4 complete

	#pragma HLS array_partition variable=feature dim=1 complete
	#pragma HLS array_partition variable=output dim = 1 complete

	col_out: for(int x_out = 0; x_out < OUT_DIM; x_out ++) {
		row_out: for(int y_out = 0; y_out < OUT_DIM; y_out ++){
			#pragma HLS pipeline
			row_k: for (int y_k = 0; y_k < KERN_DIM; y_k ++){
				col_k: for (int x_k = 0; x_k < KERN_DIM; x_k ++) {
					ch_in: for(int c_in = 0; c_in < CH_IN; c_in ++) {
						ch_out: for(int c_out = 0; c_out < CH_OUT; c_out ++) {
							output[c_out][y_out][x_out] += kernel[c_out][c_in][y_k][x_k]*feature[c_in][y_k + y_out][x_k + x_out];
						}
					}
				}

			}
		}
	}
}



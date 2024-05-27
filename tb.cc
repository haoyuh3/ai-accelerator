#include <iostream>
#include <stdlib.h>
#include "top.h"

using namespace std;

int main(int argc, char **argv)
{
	int32 feature[CH_IN][FEAT_DIM][FEAT_DIM];
	int32 kernel[CH_OUT][CH_IN][KERN_DIM][KERN_DIM];
	int32 output[CH_OUT][OUT_DIM][OUT_DIM];
	int32 sw_result[CH_OUT][OUT_DIM][OUT_DIM];
	int err_cnt = 0;

	// Generate the expected result
	// Iterate over the rows of the A matrix

	for (int i = 0; i < FEAT_DIM; i ++) {
		for (int j = 0; j < FEAT_DIM; j ++) {
			for (int k = 0; k < CH_IN; k ++) {
				feature[k][i][j] = rand()%100 - 50;
			}
		}
	}
	for (int i = 0; i < KERN_DIM; i ++) {
		for (int j = 0; j < KERN_DIM; j ++) {
			for (int c_i = 0; c_i < CH_IN; c_i ++) {
				for (int c_o = 0; c_o < CH_OUT; c_o ++) {
					kernel[c_o][c_i][i][j] = rand()%100 - 50;
				}
			}
		}
	}

	// Software


	row_out: for(int y_out = 0; y_out < OUT_DIM; y_out ++) {
		col_out: for(int x_out = 0; x_out < OUT_DIM; x_out ++) {
			ch_out: for(int c_out = 0; c_out < CH_OUT; c_out ++) {
				int32 acc = 0;
				ch_in: for(int c_in = 0; c_in < CH_IN; c_in ++) {
					row_k: for (int y_k = 0; y_k < KERN_DIM; y_k ++) {
						col_k: for (int x_k = 0; x_k < KERN_DIM; x_k ++) {
							acc += kernel[c_out][c_in][y_k][x_k]*feature[c_in][y_k + y_out][x_k + x_out];
						}
					}
				}
				sw_result[c_out][y_out][x_out] = acc;
			}
		}
	}



	// Hardware
#ifdef C_SIM
	conv(feature, kernel, output);
#endif
	// Check Results
	for (int p = 0; p < OUT_DIM; p++) {
		for (int q = 0; q < OUT_DIM; q++) {
			for (int r = 0; r < CH_OUT; r ++) {
#ifdef C_SIM
			// Check HW result against SW
				if (output[r][p][q] != sw_result[r][p][q]) {
					err_cnt++;
				}
#else
			cout << sw_result[r][p][q];
#endif
			}
		}
	}

#ifdef C_SIM
	if (err_cnt)
		cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
	else
		cout << "Test passes." << endl;
#endif
	return err_cnt;
}

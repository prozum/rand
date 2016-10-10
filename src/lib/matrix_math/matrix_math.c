#include "matrix_math.h"

void mult_mat_mat(double m1[][], double m2[][]) {
    int m1_size = sizeof(m1) / sizeof(double);
    int m2_size = sizeof(m2) / sizeof(double);

    if(m1_size != m2_size) {
        LOG_WARNING(SENDER_BOARD, "Cannot multiply matrices of different size.");
        return;
    }
}

void mult_mat_vec(double *m, double *v) {

}

void mat_T(double *m){

}


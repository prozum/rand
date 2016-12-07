#include <stdio.h>
#include "libfixmath/fix16.h"

int main(int argc, char *argv[]) {
    fix16_t val1 = fix16_from_float(64.123);
    fix16_t val2 = fix16_from_float(101.947);

    fix16_t res_mult = fix16_mul(val1, val2);
    fix16_t res_div = fix16_div(val2, val1);
    fix16_t res_min = -val1;

    printf("val1 = %f, val2 = %f\nmult = %f\ndiv = %f\n", fix16_to_float(val1), fix16_to_float(val2),
           fix16_to_float(res_mult), fix16_to_float(res_div));
    printf("-val1 = %f\n", fix16_to_float(res_min));

    fix16_t res_ang = fix16_sin(fix16_from_float(90.0f));
    printf("angle = %f\n", fix16_to_float(res_ang));
}


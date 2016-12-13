#include <stdio.h>
#include "libfixmath/fix16.h"

#define __USE_MISC
#include "math.h"

int main(int argc, char *argv[]) {
    fix16_t val1 = fix16_from_float(64.123);
    fix16_t val2 = fix16_from_float(101.947);

    fix16_t res_mult = fix16_mul(val1, val2);
    fix16_t res_div = fix16_div(val2, val1);
    fix16_t res_min = -val1;

    printf("val1 = %f, val2 = %f\nmult = %f\ndiv = %f\n", fix16_to_float(val1), fix16_to_float(val2),
           fix16_to_float(res_mult), fix16_to_float(res_div));
    printf("-val1 = %f\n", fix16_to_float(res_min));

    fix16_t res_atan2 = fix16_atan2(fix16_from_int(10), fix16_from_int(1));
    printf("atan2 = %f\n", fix16_to_float(res_atan2));
    printf("\n");

    fix16_t cases[] = {
            fix16_from_dbl(M_PI * 0.0),
            fix16_from_dbl(M_PI * 0.5),
            fix16_from_dbl(M_PI * 1.0),
            fix16_from_dbl(M_PI * 1.5),
            fix16_from_dbl(M_PI * 2.0),
    };

    for (int i = 0; i < sizeof(cases)/sizeof(fix16_t); i++ ) {
        printf("val: %f\n", fix16_to_float(cases[i]));

        fix16_t res_sin = fix16_sin(cases[i]);
        fix16_t res_asin = fix16_asin(res_sin);
        printf("sin = %f\n", fix16_to_float(res_sin));
        printf("asin = %f\n", fix16_to_float(res_asin));

        fix16_t res_cos = fix16_cos(cases[i]);
        fix16_t res_acos = fix16_acos(res_cos);
        printf("cos = %f\n", fix16_to_float(res_cos));
        printf("acos = %f\n", fix16_to_float(res_acos));

        fix16_t res_tan = fix16_tan(cases[i]);
        fix16_t res_atan = fix16_atan(res_tan);
        printf("tan = %f\n", fix16_to_float(res_tan));
        printf("atan = %f\n", fix16_to_float(res_atan));
        printf("\n");
    }
}


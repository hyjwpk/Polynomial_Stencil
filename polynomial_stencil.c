#include <stdlib.h>

void polynomial_stencil(double *fa, double *f, long nx, double p[], int term) {
    int idx = term / 2;
#pragma omp parallel for
    for (long i = 0; i < nx; i++) {
        double result = 0;
        for (int j = 0; j < term; j++) {
            long offset = i + j - idx;
            if (offset < 0 || offset >= nx) {
                continue;
            }
            double x = f[offset];
            double x_t = x;
            int t = abs(j - idx);
            for (int k = 1; k < t; k++) {
                x_t *= x;
            }
            result += x_t * p[j];
        }
        fa[i] = result;
    }
}

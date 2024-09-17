#include <stdlib.h>

void polynomial_stencil(double *fa, double *f, long nx, double p[], int term) {
    int idx = term / 2;
    long block = nx / 288;
#pragma omp parallel for
    for (long ii = 0; ii < nx - block + 1; ii += block) {
        for (long i = ii; i < ii + block; i++) {
            double x = f[i];
            double x_t = x;
            fa[i] += x_t * p[idx];
            for (int j = 1; j <= idx; j++) {
                if (j > 1) {
                    x_t *= x;
                }
                long offset = i + j;
                if (offset >= ii && offset < ii + block) {
                    fa[offset] += x_t * p[idx - j];
                }
                offset = i - j;
                if (offset >= ii && offset < ii + block) {
                    fa[offset] += x_t * p[idx + j];
                }
            }
        }
    }
#pragma omp parallel for
    for (long ii = 0; ii < nx - block + 1; ii += block) {
        for (int j = 1; j <= idx && ii - j >= 0; j++) {
            double x = f[ii - j];
            double x_t = 1;
            for (int jj = 1; jj <= idx && -j + jj < block; jj++) {
                x_t *= x;
                if (-j + jj >= 0) {
                    fa[ii - j + jj] += x_t * p[idx - jj];
                }
            }
        }
        for (int j = 1; j <= idx && ii + block - 1 + j < nx; j++) {
            double x = f[ii + block - 1 + j];
            double x_t = 1;
            for (int jj = 1; jj <= idx && block - 1 + j - jj >= 0; jj++) {
                x_t *= x;
                if (j - jj <= 0) {
                    fa[ii + block - 1 + j - jj] += x_t * p[idx + jj];
                }
            }
        }
    }
#pragma omp parallel for
    for (long i = block * 288; i < nx; i++) {
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

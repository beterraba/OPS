//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_norm2_kernel;

#undef OPS_ACC0

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_norm2_kernel * (y))

// user function

void tea_leaf_norm2_kernel_c_wrapper(double *p_a0, int base0, int tot0,
                                     double *p_a1, int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
  double p_a1_0 = p_a1[0];
#pragma omp target enter data map(to : p_a0[0 : tot0])
#ifdef OPS_GPU

#pragma omp target map(to : p_a0[0 : tot0]) map(tofrom : p_a1_0)
#pragma omp teams num_teams(num_blocks) thread_limit(128) reduction(+ : p_a1_0)
#pragma omp distribute parallel for simd collapse(2)                           \
    schedule(static, 1) reduction(+ : p_a1_0)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      const double *x = p_a0 + base0 + n_x * 1 * 1 +
                        n_y * xdim0_tea_leaf_norm2_kernel * 1 * 1;

      double *norm = &p_a1_0;

      *norm = *norm + x[OPS_ACC0(0, 0)] * x[OPS_ACC0(0, 0)];
    }
  }
  p_a1[0] = p_a1_0;
}
#undef OPS_ACC0
//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_set_field_kernel;
extern int xdim1_set_field_kernel;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y) (x + xdim0_set_field_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_set_field_kernel * (y))

// user function

void set_field_kernel_c_wrapper(double *p_a0, int base0, int tot0, double *p_a1,
                                int base1, int tot1, int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(to : p_a0[0 : tot0], p_a1[0 : tot1])
#ifdef OPS_GPU

#pragma omp target map(to : p_a0[0 : tot0], p_a1[0 : tot1])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(2) schedule(static, 1)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      const double *energy0 =
          p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_set_field_kernel * 1 * 1;

      double *energy1 =
          p_a1 + base1 + n_x * 1 * 1 + n_y * xdim1_set_field_kernel * 1 * 1;

      energy1[OPS_ACC1(0, 0)] = energy0[OPS_ACC0(0, 0)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
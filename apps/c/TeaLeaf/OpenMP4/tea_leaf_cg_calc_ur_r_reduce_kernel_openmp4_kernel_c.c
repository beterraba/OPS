//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel;
extern int xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel * (y))

// user function

void tea_leaf_cg_calc_ur_r_reduce_kernel_c_wrapper(double *p_a0, int base0,
                                                   int tot0, double *p_a1,
                                                   int base1, int tot1,
                                                   double p_a2, double *p_a3,
                                                   int x_size, int y_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
  double p_a3_0 = p_a3[0];
#pragma omp target enter data map(to : p_a0[0 : tot0], p_a1[0 : tot1])
#ifdef OPS_GPU

#pragma omp target map(to : p_a0[0 : tot0], p_a1[0 : tot1]) map(tofrom : p_a3_0)
#pragma omp teams num_teams(num_blocks) thread_limit(128) reduction(+ : p_a3_0)
#pragma omp distribute parallel for simd collapse(2)                           \
    schedule(static, 1) reduction(+ : p_a3_0)
#endif
  for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
    for (int n_x = 0; n_x < x_size; n_x++) {
      double *r = p_a0 + base0 + n_x * 1 * 1 +
                  n_y * xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel * 1 * 1;

      const double *w = p_a1 + base1 + n_x * 1 * 1 +
                        n_y * xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel * 1 * 1;
      const double *alpha = &p_a2;

      double *rnn = &p_a3_0;

      r[OPS_ACC0(0, 0)] = r[OPS_ACC0(0, 0)] - (*alpha) * w[OPS_ACC1(0, 0)];
      *rnn = *rnn + r[OPS_ACC0(0, 0)] * r[OPS_ACC0(0, 0)];
    }
  }
  p_a3[0] = p_a3_0;
}
#undef OPS_ACC0
#undef OPS_ACC1
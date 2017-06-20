//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_mom_kernel_z3;
extern int ydim0_advec_mom_kernel_z3;
extern int xdim1_advec_mom_kernel_z3;
extern int ydim1_advec_mom_kernel_z3;
extern int xdim2_advec_mom_kernel_z3;
extern int ydim2_advec_mom_kernel_z3;
extern int xdim3_advec_mom_kernel_z3;
extern int ydim3_advec_mom_kernel_z3;

#undef OPS_OPENMP40
#undef OPS_OPENMP41
#undef OPS_OPENMP42
#undef OPS_OPENMP43

#define OPS_OPENMP40(x, y, z)                                                  \
  (x + xdim0_advec_mom_kernel_z3 * (y) +                                       \
   xdim0_advec_mom_kernel_z3 * ydim0_advec_mom_kernel_z3 * (z))
#define OPS_OPENMP41(x, y, z)                                                  \
  (x + xdim1_advec_mom_kernel_z3 * (y) +                                       \
   xdim1_advec_mom_kernel_z3 * ydim1_advec_mom_kernel_z3 * (z))
#define OPS_OPENMP42(x, y, z)                                                  \
  (x + xdim2_advec_mom_kernel_z3 * (y) +                                       \
   xdim2_advec_mom_kernel_z3 * ydim2_advec_mom_kernel_z3 * (z))
#define OPS_OPENMP43(x, y, z)                                                  \
  (x + xdim3_advec_mom_kernel_z3 * (y) +                                       \
   xdim3_advec_mom_kernel_z3 * ydim3_advec_mom_kernel_z3 * (z))

// user function

void advec_mom_kernel_z3_c_wrapper(double *p_a0, int base0, int tot0,
                                   double *p_a1, int base1, int tot1,
                                   double *p_a2, int base2, int tot2,
                                   double *p_a3, int base3, int tot3,
                                   int x_size, int y_size, int z_size) {
  int num_blocks = round(((double)x_size * (double)y_size) / 128);
#pragma omp target enter data map(                                             \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2], p_a3[0 : tot3])
#ifdef OPS_GPU

#pragma omp target map(                                                        \
    to : p_a0[0 : tot0], p_a1[0 : tot1], p_a2[0 : tot2], p_a3[0 : tot3])
#pragma omp teams num_teams(num_blocks) thread_limit(128)
#pragma omp distribute parallel for simd collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        double *pre_vol =
            p_a0 + base0 + n_x * 1 * 1 +
            n_y * xdim0_advec_mom_kernel_z3 * 1 * 1 +
            n_z * xdim0_advec_mom_kernel_z3 * ydim0_advec_mom_kernel_z3 * 1;

        double *post_vol =
            p_a1 + base1 + n_x * 1 * 1 +
            n_y * xdim1_advec_mom_kernel_z3 * 1 * 1 +
            n_z * xdim1_advec_mom_kernel_z3 * ydim1_advec_mom_kernel_z3 * 1;

        const double *volume =
            p_a2 + base2 + n_x * 1 * 1 +
            n_y * xdim2_advec_mom_kernel_z3 * 1 * 1 +
            n_z * xdim2_advec_mom_kernel_z3 * ydim2_advec_mom_kernel_z3 * 1;

        const double *vol_flux_z =
            p_a3 + base3 + n_x * 1 * 1 +
            n_y * xdim3_advec_mom_kernel_z3 * 1 * 1 +
            n_z * xdim3_advec_mom_kernel_z3 * ydim3_advec_mom_kernel_z3 * 1;

        post_vol[OPS_ACC1(0, 0, 0)] = volume[OPS_ACC2(0, 0, 0)];
        pre_vol[OPS_ACC0(0, 0, 0)] = post_vol[OPS_ACC1(0, 0, 0)] +
                                     vol_flux_z[OPS_ACC3(0, 0, 1)] -
                                     vol_flux_z[OPS_ACC3(0, 0, 0)];
      }
    }
  }
}
#undef OPS_OPENMP40
#undef OPS_OPENMP41
#undef OPS_OPENMP42
#undef OPS_OPENMP43
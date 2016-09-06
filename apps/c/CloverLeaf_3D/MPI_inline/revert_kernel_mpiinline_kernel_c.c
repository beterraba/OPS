//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_revert_kernel;
int ydim0_revert_kernel;
int xdim1_revert_kernel;
int ydim1_revert_kernel;
int xdim2_revert_kernel;
int ydim2_revert_kernel;
int xdim3_revert_kernel;
int ydim3_revert_kernel;

#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_revert_kernel * 1 +                                   \
   n_z * xdim0_revert_kernel * ydim0_revert_kernel * 1 + x +                   \
   xdim0_revert_kernel * (y) +                                                 \
   xdim0_revert_kernel * ydim0_revert_kernel * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_revert_kernel * 1 +                                   \
   n_z * xdim1_revert_kernel * ydim1_revert_kernel * 1 + x +                   \
   xdim1_revert_kernel * (y) +                                                 \
   xdim1_revert_kernel * ydim1_revert_kernel * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim2_revert_kernel * 1 +                                   \
   n_z * xdim2_revert_kernel * ydim2_revert_kernel * 1 + x +                   \
   xdim2_revert_kernel * (y) +                                                 \
   xdim2_revert_kernel * ydim2_revert_kernel * (z))
#define OPS_ACC3(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim3_revert_kernel * 1 +                                   \
   n_z * xdim3_revert_kernel * ydim3_revert_kernel * 1 + x +                   \
   xdim3_revert_kernel * (y) +                                                 \
   xdim3_revert_kernel * ydim3_revert_kernel * (z))

// user function

void revert_kernel_c_wrapper(const double *restrict density0,
                             double *restrict density1,
                             const double *restrict energy0,
                             double *restrict energy1, int x_size, int y_size,
                             int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {

        density1[OPS_ACC1(0, 0, 0)] = density0[OPS_ACC0(0, 0, 0)];
        energy1[OPS_ACC3(0, 0, 0)] = energy0[OPS_ACC2(0, 0, 0)];
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
//
// auto-generated by ops.py
//
#include "./MPI_inline/multidim_common.h"

int xdim0_multidim_copy_kernel;
int ydim0_multidim_copy_kernel;
int xdim1_multidim_copy_kernel;
int ydim1_multidim_copy_kernel;

#define OPS_ACC_MD0(d, x, y)                                                   \
  (n_x * 1 + n_y * xdim0_multidim_copy_kernel * 1 + (x) +                      \
   (d)*xdim0_multidim_copy_kernel * ydim0_multidim_copy_kernel +               \
   (xdim0_multidim_copy_kernel * (y)))
#define OPS_ACC_MD1(d, x, y)                                                   \
  (n_x * 1 + n_y * xdim1_multidim_copy_kernel * 1 + (x) +                      \
   (d)*xdim1_multidim_copy_kernel * ydim1_multidim_copy_kernel +               \
   (xdim1_multidim_copy_kernel * (y)))
// user function

void multidim_copy_kernel_c_wrapper(const double *restrict src,
                                    double *restrict dest, int x_size,
                                    int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {

      dest[OPS_ACC_MD1(0, 0, 0)] = src[OPS_ACC_MD0(0, 0, 0)];
      dest[OPS_ACC_MD1(1, 0, 0)] = src[OPS_ACC_MD0(1, 0, 0)];
    }
  }
}

#undef OPS_ACC_MD0
#undef OPS_ACC_MD1

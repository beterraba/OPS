//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_advec_cell_kernel4_ydir;
int xdim1_advec_cell_kernel4_ydir;
int xdim2_advec_cell_kernel4_ydir;
int xdim3_advec_cell_kernel4_ydir;
int xdim4_advec_cell_kernel4_ydir;
int xdim5_advec_cell_kernel4_ydir;
int xdim6_advec_cell_kernel4_ydir;
int xdim7_advec_cell_kernel4_ydir;
int xdim8_advec_cell_kernel4_ydir;
int xdim9_advec_cell_kernel4_ydir;
int xdim10_advec_cell_kernel4_ydir;

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 + n_y * xdim0_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim0_advec_cell_kernel4_ydir * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 + n_y * xdim1_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim1_advec_cell_kernel4_ydir * (y))
#define OPS_ACC2(x, y)                                                         \
  (n_x * 1 + n_y * xdim2_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim2_advec_cell_kernel4_ydir * (y))
#define OPS_ACC3(x, y)                                                         \
  (n_x * 1 + n_y * xdim3_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim3_advec_cell_kernel4_ydir * (y))
#define OPS_ACC4(x, y)                                                         \
  (n_x * 1 + n_y * xdim4_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim4_advec_cell_kernel4_ydir * (y))
#define OPS_ACC5(x, y)                                                         \
  (n_x * 1 + n_y * xdim5_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim5_advec_cell_kernel4_ydir * (y))
#define OPS_ACC6(x, y)                                                         \
  (n_x * 1 + n_y * xdim6_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim6_advec_cell_kernel4_ydir * (y))
#define OPS_ACC7(x, y)                                                         \
  (n_x * 1 + n_y * xdim7_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim7_advec_cell_kernel4_ydir * (y))
#define OPS_ACC8(x, y)                                                         \
  (n_x * 1 + n_y * xdim8_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim8_advec_cell_kernel4_ydir * (y))
#define OPS_ACC9(x, y)                                                         \
  (n_x * 1 + n_y * xdim9_advec_cell_kernel4_ydir * 1 + x +                     \
   xdim9_advec_cell_kernel4_ydir * (y))
#define OPS_ACC10(x, y)                                                        \
  (n_x * 1 + n_y * xdim10_advec_cell_kernel4_ydir * 1 + x +                    \
   xdim10_advec_cell_kernel4_ydir * (y))

// user function

void advec_cell_kernel4_ydir_c_wrapper(
    double *restrict density1, double *restrict energy1,
    const double *restrict mass_flux_y, const double *restrict vol_flux_y,
    const double *restrict pre_vol, const double *restrict post_vol,
    double *restrict pre_mass, double *restrict post_mass,
    double *restrict advec_vol, double *restrict post_ener,
    const double *restrict ener_flux, int x_size, int y_size) {
#pragma omp parallel for
  for (int n_y = 0; n_y < y_size; n_y++) {
    for (int n_x = 0; n_x < x_size; n_x++) {

      pre_mass[OPS_ACC6(0, 0)] =
          density1[OPS_ACC0(0, 0)] * pre_vol[OPS_ACC4(0, 0)];
      post_mass[OPS_ACC7(0, 0)] = pre_mass[OPS_ACC6(0, 0)] +
                                  mass_flux_y[OPS_ACC2(0, 0)] -
                                  mass_flux_y[OPS_ACC2(0, 1)];
      post_ener[OPS_ACC9(0, 0)] =
          (energy1[OPS_ACC1(0, 0)] * pre_mass[OPS_ACC6(0, 0)] +
           ener_flux[OPS_ACC10(0, 0)] - ener_flux[OPS_ACC10(0, 1)]) /
          post_mass[OPS_ACC7(0, 0)];
      advec_vol[OPS_ACC8(0, 0)] = pre_vol[OPS_ACC4(0, 0)] +
                                  vol_flux_y[OPS_ACC3(0, 0)] -
                                  vol_flux_y[OPS_ACC3(0, 1)];
      density1[OPS_ACC0(0, 0)] =
          post_mass[OPS_ACC7(0, 0)] / advec_vol[OPS_ACC8(0, 0)];
      energy1[OPS_ACC1(0, 0)] = post_ener[OPS_ACC9(0, 0)];
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10

//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_advec_cell_kernel3_xdir;
int ydim0_advec_cell_kernel3_xdir;
int xdim1_advec_cell_kernel3_xdir;
int ydim1_advec_cell_kernel3_xdir;
int xdim2_advec_cell_kernel3_xdir;
int ydim2_advec_cell_kernel3_xdir;
int xdim3_advec_cell_kernel3_xdir;
int ydim3_advec_cell_kernel3_xdir;
int xdim4_advec_cell_kernel3_xdir;
int ydim4_advec_cell_kernel3_xdir;
int xdim5_advec_cell_kernel3_xdir;
int ydim5_advec_cell_kernel3_xdir;
int xdim6_advec_cell_kernel3_xdir;
int ydim6_advec_cell_kernel3_xdir;
int xdim7_advec_cell_kernel3_xdir;
int ydim7_advec_cell_kernel3_xdir;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_advec_cell_kernel3_xdir * (y) +                                   \
   xdim0_advec_cell_kernel3_xdir * ydim0_advec_cell_kernel3_xdir * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_advec_cell_kernel3_xdir * (y) +                                   \
   xdim1_advec_cell_kernel3_xdir * ydim1_advec_cell_kernel3_xdir * (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_advec_cell_kernel3_xdir * (y) +                                   \
   xdim2_advec_cell_kernel3_xdir * ydim2_advec_cell_kernel3_xdir * (z))
#define OPS_ACC3(x, y, z)                                                      \
  (x + xdim3_advec_cell_kernel3_xdir * (y) +                                   \
   xdim3_advec_cell_kernel3_xdir * ydim3_advec_cell_kernel3_xdir * (z))
#define OPS_ACC4(x, y, z)                                                      \
  (x + xdim4_advec_cell_kernel3_xdir * (y) +                                   \
   xdim4_advec_cell_kernel3_xdir * ydim4_advec_cell_kernel3_xdir * (z))
#define OPS_ACC5(x, y, z)                                                      \
  (x + xdim5_advec_cell_kernel3_xdir * (y) +                                   \
   xdim5_advec_cell_kernel3_xdir * ydim5_advec_cell_kernel3_xdir * (z))
#define OPS_ACC6(x, y, z)                                                      \
  (x + xdim6_advec_cell_kernel3_xdir * (y) +                                   \
   xdim6_advec_cell_kernel3_xdir * ydim6_advec_cell_kernel3_xdir * (z))
#define OPS_ACC7(x, y, z)                                                      \
  (x + xdim7_advec_cell_kernel3_xdir * (y) +                                   \
   xdim7_advec_cell_kernel3_xdir * ydim7_advec_cell_kernel3_xdir * (z))

// user function

inline void advec_cell_kernel3_xdir(const double *vol_flux_x,
                                    const double *pre_vol, const int *xx,
                                    const double *vertexdx,
                                    const double *density1,
                                    const double *energy1, double *mass_flux_x,
                                    double *ener_flux) {

  double sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0 / 6.0;

  int x_max = field.x_max;

  int upwind, donor, downwind, dif;

  if (vol_flux_x[OPS_ACC0(0, 0, 0)] > 0.0) {
    upwind = -2;
    donor = -1;
    downwind = 0;
    dif = donor;
  } else if (xx[OPS_ACC2(1, 0, 0)] < x_max + 2 - 2) {
    upwind = 1;
    donor = 0;
    downwind = -1;
    dif = upwind;
  } else {
    upwind = 0;
    donor = 0;
    downwind = -1;
    dif = upwind;
  }

  sigmat = fabs(vol_flux_x[OPS_ACC0(0, 0, 0)]) / pre_vol[OPS_ACC1(donor, 0, 0)];
  sigma3 = (1.0 + sigmat) *
           (vertexdx[OPS_ACC3(0, 0, 0)] / vertexdx[OPS_ACC3(dif, 0, 0)]);
  sigma4 = 2.0 - sigmat;

  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(donor, 0, 0)] - density1[OPS_ACC4(upwind, 0, 0)];
  diffdw = density1[OPS_ACC4(downwind, 0, 0)] - density1[OPS_ACC4(donor, 0, 0)];

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmav) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  mass_flux_x[OPS_ACC6(0, 0, 0)] = (vol_flux_x[OPS_ACC0(0, 0, 0)]) *
                                   (density1[OPS_ACC4(donor, 0, 0)] + limiter);

  sigmam = fabs(mass_flux_x[OPS_ACC6(0, 0, 0)]) /
           (density1[OPS_ACC4(donor, 0, 0)] * pre_vol[OPS_ACC1(donor, 0, 0)]);
  diffuw = energy1[OPS_ACC5(donor, 0, 0)] - energy1[OPS_ACC5(upwind, 0, 0)];
  diffdw = energy1[OPS_ACC5(downwind, 0, 0)] - energy1[OPS_ACC5(donor, 0, 0)];

  if ((diffuw * diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0, diffdw) *
              MIN(MIN(fabs(diffuw), fabs(diffdw)),
                  one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter = 0.0;

  ener_flux[OPS_ACC7(0, 0, 0)] = mass_flux_x[OPS_ACC6(0, 0, 0)] *
                                 (energy1[OPS_ACC5(donor, 0, 0)] + limiter);
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7

void advec_cell_kernel3_xdir_c_wrapper(double *p_a0, double *p_a1, int *p_a2,
                                       double *p_a3, double *p_a4, double *p_a5,
                                       double *p_a6, double *p_a7, int x_size,
                                       int y_size, int z_size) {
#ifdef OPS_GPU
#pragma acc parallel deviceptr(p_a0, p_a1, p_a2, p_a3, p_a4, p_a5, p_a6, p_a7)
#pragma acc loop
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
    for (int n_y = 0; n_y < y_size; n_y++) {
#ifdef OPS_GPU
#pragma acc loop
#endif
      for (int n_x = 0; n_x < x_size; n_x++) {
        advec_cell_kernel3_xdir(
            p_a0 + n_x * 1 * 1 + n_y * xdim0_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim0_advec_cell_kernel3_xdir *
                    ydim0_advec_cell_kernel3_xdir * 1,
            p_a1 + n_x * 1 * 1 + n_y * xdim1_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim1_advec_cell_kernel3_xdir *
                    ydim1_advec_cell_kernel3_xdir * 1,
            p_a2 + n_x * 1 * 1 + n_y * xdim2_advec_cell_kernel3_xdir * 0 * 1 +
                n_z * xdim2_advec_cell_kernel3_xdir *
                    ydim2_advec_cell_kernel3_xdir * 0,
            p_a3 + n_x * 1 * 1 + n_y * xdim3_advec_cell_kernel3_xdir * 0 * 1 +
                n_z * xdim3_advec_cell_kernel3_xdir *
                    ydim3_advec_cell_kernel3_xdir * 0,
            p_a4 + n_x * 1 * 1 + n_y * xdim4_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim4_advec_cell_kernel3_xdir *
                    ydim4_advec_cell_kernel3_xdir * 1,
            p_a5 + n_x * 1 * 1 + n_y * xdim5_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim5_advec_cell_kernel3_xdir *
                    ydim5_advec_cell_kernel3_xdir * 1,
            p_a6 + n_x * 1 * 1 + n_y * xdim6_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim6_advec_cell_kernel3_xdir *
                    ydim6_advec_cell_kernel3_xdir * 1,
            p_a7 + n_x * 1 * 1 + n_y * xdim7_advec_cell_kernel3_xdir * 1 * 1 +
                n_z * xdim7_advec_cell_kernel3_xdir *
                    ydim7_advec_cell_kernel3_xdir * 1);
      }
    }
  }
}

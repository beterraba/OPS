//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_advec_mom_kernel2_y;
extern int xdim1_advec_mom_kernel2_y;
extern int xdim2_advec_mom_kernel2_y;
extern int xdim3_advec_mom_kernel2_y;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3

#define OPS_ACC0(x, y) (x + xdim0_advec_mom_kernel2_y * (y))
#define OPS_ACC1(x, y) (x + xdim1_advec_mom_kernel2_y * (y))
#define OPS_ACC2(x, y) (x + xdim2_advec_mom_kernel2_y * (y))
#define OPS_ACC3(x, y) (x + xdim3_advec_mom_kernel2_y * (y))

// user function

void advec_mom_kernel2_y_c_wrapper(double *p_a0, int base0, int tot0,
                                   double *p_a1, int base1, int tot1,
                                   double *p_a2, int base2, int tot2,
                                   double *p_a3, int base3, int tot3,
                                   int x_size, int y_size) {
  int num_blocks = OPS_threads;
#pragma omp target enter data map(                                             \
    to : p_a0[0 : tot0], p_a1[0 : tot1],                                       \
                              p_a2[0 : tot2],                                  \
                                   p_a3[0 : tot3],                             \
                                        states[0 : number_of_states])
#ifdef OPS_GPU

#pragma omp target teams num_teams(num_blocks)                                 \
    thread_limit(OPS_threads_for_block)
#pragma omp distribute parallel for simd schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
#ifdef OPS_GPU
#endif
    int n_x = i % x_size;
    int n_y = i / x_size;
    double *vel1 =
        p_a0 + base0 + n_x * 1 * 1 + n_y * xdim0_advec_mom_kernel2_y * 1 * 1;

    const double *node_mass_post =
        p_a1 + base1 + n_x * 1 * 1 + n_y * xdim1_advec_mom_kernel2_y * 1 * 1;
    const double *node_mass_pre =
        p_a2 + base2 + n_x * 1 * 1 + n_y * xdim2_advec_mom_kernel2_y * 1 * 1;

    const double *mom_flux =
        p_a3 + base3 + n_x * 1 * 1 + n_y * xdim3_advec_mom_kernel2_y * 1 * 1;

    vel1[OPS_ACC0(0, 0)] =
        (vel1[OPS_ACC0(0, 0)] * node_mass_pre[OPS_ACC2(0, 0)] +
         mom_flux[OPS_ACC3(0, -1)] - mom_flux[OPS_ACC3(0, 0)]) /
        node_mass_post[OPS_ACC1(0, 0)];
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
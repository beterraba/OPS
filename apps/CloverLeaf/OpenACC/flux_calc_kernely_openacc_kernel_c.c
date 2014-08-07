//
// auto-generated by ops.py on 2014-07-31 11:59
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_flux_calc_kernely;
int xdim1_flux_calc_kernely;
int xdim2_flux_calc_kernely;
int xdim3_flux_calc_kernely;

#define OPS_ACC0(x,y) (x+xdim0_flux_calc_kernely*(y))
#define OPS_ACC1(x,y) (x+xdim1_flux_calc_kernely*(y))
#define OPS_ACC2(x,y) (x+xdim2_flux_calc_kernely*(y))
#define OPS_ACC3(x,y) (x+xdim3_flux_calc_kernely*(y))

//user function
inline 
void flux_calc_kernely( double *vol_flux_y, const double *yarea,
                        const double *yvel0, const double *yvel1) {

  vol_flux_y[OPS_ACC0(0,0)] = 0.25 * dt * (yarea[OPS_ACC1(0,0)]) *
  ( (yvel0[OPS_ACC2(0,0)]) + (yvel0[OPS_ACC2(1,0)]) + (yvel1[OPS_ACC3(0,0)]) + (yvel1[OPS_ACC3(1,0)]) );

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


void flux_calc_kernely_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      flux_calc_kernely(  p_a0 + n_x*1 + n_y*xdim0_flux_calc_kernely*1,
           p_a1 + n_x*1 + n_y*xdim1_flux_calc_kernely*1, p_a2 + n_x*1 + n_y*xdim2_flux_calc_kernely*1,
           p_a3 + n_x*1 + n_y*xdim3_flux_calc_kernely*1 );

    }
  }
}

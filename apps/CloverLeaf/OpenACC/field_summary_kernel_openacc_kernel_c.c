//
// auto-generated by ops.py on 2014-06-25 11:17
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_field_summary_kernel;
int xdim1_field_summary_kernel;
int xdim2_field_summary_kernel;
int xdim3_field_summary_kernel;
int xdim4_field_summary_kernel;
int xdim5_field_summary_kernel;

#define OPS_ACC0(x,y) (x+xdim0_field_summary_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_field_summary_kernel*(y))
#define OPS_ACC2(x,y) (x+xdim2_field_summary_kernel*(y))
#define OPS_ACC3(x,y) (x+xdim3_field_summary_kernel*(y))
#define OPS_ACC4(x,y) (x+xdim4_field_summary_kernel*(y))
#define OPS_ACC5(x,y) (x+xdim5_field_summary_kernel*(y))

//user function
inline 
void field_summary_kernel( const double *volume, const double *density0,
                     const double *energy0, const double *pressure,
                     const double *xvel0,
                     const double *yvel0,
                     double *vol,
                     double *mass,
                     double *ie,
                     double *ke,
                     double *press) {

  double vsqrd, cell_vol, cell_mass;



  vsqrd = 0.0;
  vsqrd = vsqrd + 0.25 * ( xvel0[OPS_ACC4(0,0)] * xvel0[OPS_ACC4(0,0)] + yvel0[OPS_ACC5(0,0)] * yvel0[OPS_ACC5(0,0)]);
  vsqrd = vsqrd + 0.25 * ( xvel0[OPS_ACC4(1,0)] * xvel0[OPS_ACC4(1,0)] + yvel0[OPS_ACC5(1,0)] * yvel0[OPS_ACC5(1,0)]);
  vsqrd = vsqrd + 0.25 * ( xvel0[OPS_ACC4(0,1)] * xvel0[OPS_ACC4(0,1)] + yvel0[OPS_ACC5(0,1)] * yvel0[OPS_ACC5(0,1)]);
  vsqrd = vsqrd + 0.25 * ( xvel0[OPS_ACC4(1,1)] * xvel0[OPS_ACC4(1,1)] + yvel0[OPS_ACC5(1,1)] * yvel0[OPS_ACC5(1,1)]);

  cell_vol = volume[OPS_ACC0(0,0)];
  cell_mass = cell_vol * density0[OPS_ACC1(0,0)];
  *vol = *vol + cell_vol;
  *mass = *mass + cell_mass;
  *ie = *ie + cell_mass * energy0[OPS_ACC2(0,0)];
  *ke = *ke + cell_mass * 0.5 * vsqrd;
  *press = *press + cell_vol * pressure[OPS_ACC3(0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5


void field_summary_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  double *p_a7,
  double *p_a8,
  double *p_a9,
  double *p_a10,
  int x_size, int y_size) {
  double p_a6_l = *p_a6;
  double p_a7_l = *p_a7;
  double p_a8_l = *p_a8;
  double p_a9_l = *p_a9;
  double p_a10_l = *p_a10;
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5) reduction(+:p_a6_l) reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l)
  #pragma acc loop reduction(+:p_a6_l) reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a6_l) reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      field_summary_kernel(  p_a0 + n_x*1 + n_y*xdim0_field_summary_kernel*1,
           p_a1 + n_x*1 + n_y*xdim1_field_summary_kernel*1, p_a2 + n_x*1 + n_y*xdim2_field_summary_kernel*1,
           p_a3 + n_x*1 + n_y*xdim3_field_summary_kernel*1, p_a4 + n_x*1 + n_y*xdim4_field_summary_kernel*1,
           p_a5 + n_x*1 + n_y*xdim5_field_summary_kernel*1, &p_a6_l,
           &p_a7_l, &p_a8_l,
           &p_a9_l, &p_a10_l );

    }
  }
  *p_a6 = p_a6_l;
  *p_a7 = p_a7_l;
  *p_a8 = p_a8_l;
  *p_a9 = p_a9_l;
  *p_a10 = p_a10_l;
}

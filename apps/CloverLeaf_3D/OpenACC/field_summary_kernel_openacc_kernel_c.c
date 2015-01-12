//
// auto-generated by ops.py
//
#include "./OpenACC/clover_leaf_common.h"

int xdim0_field_summary_kernel;
int ydim0_field_summary_kernel;
int xdim1_field_summary_kernel;
int ydim1_field_summary_kernel;
int xdim2_field_summary_kernel;
int ydim2_field_summary_kernel;
int xdim3_field_summary_kernel;
int ydim3_field_summary_kernel;
int xdim4_field_summary_kernel;
int ydim4_field_summary_kernel;
int xdim5_field_summary_kernel;
int ydim5_field_summary_kernel;
int xdim6_field_summary_kernel;
int ydim6_field_summary_kernel;

#define OPS_ACC0(x,y,z) (x+xdim0_field_summary_kernel*(y)+xdim0_field_summary_kernel*ydim0_field_summary_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_field_summary_kernel*(y)+xdim1_field_summary_kernel*ydim1_field_summary_kernel*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_field_summary_kernel*(y)+xdim2_field_summary_kernel*ydim2_field_summary_kernel*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_field_summary_kernel*(y)+xdim3_field_summary_kernel*ydim3_field_summary_kernel*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_field_summary_kernel*(y)+xdim4_field_summary_kernel*ydim4_field_summary_kernel*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_field_summary_kernel*(y)+xdim5_field_summary_kernel*ydim5_field_summary_kernel*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_field_summary_kernel*(y)+xdim6_field_summary_kernel*ydim6_field_summary_kernel*(z))

//user function
inline 
void field_summary_kernel( const double *volume, const double *density0,
                     const double *energy0, const double *pressure,
                     const double *xvel0,
                     const double *yvel0,
                     const double *zvel0,
                     double *vol,
                     double *mass,
                     double *ie,
                     double *ke,
                     double *press) {

  double vsqrd, cell_vol, cell_mass;

  vsqrd = 0.0;
  vsqrd+=0.125*( xvel0[OPS_ACC4(0,0,0)] * xvel0[OPS_ACC4(0,0,0)] +
                 yvel0[OPS_ACC5(0,0,0)] * yvel0[OPS_ACC5(0,0,0)] +
                 zvel0[OPS_ACC6(0,0,0)] * zvel0[OPS_ACC6(0,0,0)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(1,0,0)] * xvel0[OPS_ACC4(1,0,0)] +
                 yvel0[OPS_ACC5(1,0,0)] * yvel0[OPS_ACC5(1,0,0)] +
                 zvel0[OPS_ACC6(1,0,0)] * zvel0[OPS_ACC6(1,0,0)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(0,1,0)] * xvel0[OPS_ACC4(0,1,0)] +
                 yvel0[OPS_ACC5(0,1,0)] * yvel0[OPS_ACC5(0,1,0)] +
                 zvel0[OPS_ACC6(0,1,0)] * zvel0[OPS_ACC6(0,1,0)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(1,1,0)] * xvel0[OPS_ACC4(1,1,0)] +
                 yvel0[OPS_ACC5(1,1,0)] * yvel0[OPS_ACC5(1,1,0)] +
                 zvel0[OPS_ACC6(1,1,0)] * zvel0[OPS_ACC6(1,1,0)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(0,0,1)] * xvel0[OPS_ACC4(0,0,1)] +
                 yvel0[OPS_ACC5(0,0,1)] * yvel0[OPS_ACC5(0,0,1)] +
                 zvel0[OPS_ACC6(0,0,1)] * zvel0[OPS_ACC6(0,0,1)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(1,0,1)] * xvel0[OPS_ACC4(1,0,1)] +
                 yvel0[OPS_ACC5(1,0,1)] * yvel0[OPS_ACC5(1,0,1)] +
                 zvel0[OPS_ACC6(1,0,1)] * zvel0[OPS_ACC6(1,0,1)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(0,1,1)] * xvel0[OPS_ACC4(0,1,1)] +
                 yvel0[OPS_ACC5(0,1,1)] * yvel0[OPS_ACC5(0,1,1)] +
                 zvel0[OPS_ACC6(0,1,1)] * zvel0[OPS_ACC6(0,1,1)]);
  vsqrd+=0.125*( xvel0[OPS_ACC4(1,1,1)] * xvel0[OPS_ACC4(1,1,1)] +
                 yvel0[OPS_ACC5(1,1,1)] * yvel0[OPS_ACC5(1,1,1)] +
                 zvel0[OPS_ACC6(1,1,1)] * zvel0[OPS_ACC6(1,1,1)]);

  cell_vol = volume[OPS_ACC0(0,0,0)];
  cell_mass = cell_vol * density0[OPS_ACC1(0,0,0)];
  *vol = *vol + cell_vol;
  *mass = *mass + cell_mass;
  *ie = *ie + cell_mass * energy0[OPS_ACC2(0,0,0)];
  *ke = *ke + cell_mass * 0.5 * vsqrd;
  *press = *press + cell_vol * pressure[OPS_ACC3(0,0,0)];

}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6



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
  double *p_a11,
  int x_size, int y_size, int z_size) {
  double p_a7_l = *p_a7;
  double p_a8_l = *p_a8;
  double p_a9_l = *p_a9;
  double p_a10_l = *p_a10;
  double p_a11_l = *p_a11;
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6) reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l) reduction(+:p_a11_l)
  #pragma acc loop reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l) reduction(+:p_a11_l)
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l) reduction(+:p_a11_l)
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop reduction(+:p_a7_l) reduction(+:p_a8_l) reduction(+:p_a9_l) reduction(+:p_a10_l) reduction(+:p_a11_l)
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        field_summary_kernel(  p_a0 + n_x*1*1 + n_y*xdim0_field_summary_kernel*1*1 + n_z*xdim0_field_summary_kernel*ydim0_field_summary_kernel*1,
           p_a1 + n_x*1*1 + n_y*xdim1_field_summary_kernel*1*1 + n_z*xdim1_field_summary_kernel*ydim1_field_summary_kernel*1,
           p_a2 + n_x*1*1 + n_y*xdim2_field_summary_kernel*1*1 + n_z*xdim2_field_summary_kernel*ydim2_field_summary_kernel*1,
           p_a3 + n_x*1*1 + n_y*xdim3_field_summary_kernel*1*1 + n_z*xdim3_field_summary_kernel*ydim3_field_summary_kernel*1,
           p_a4 + n_x*1*1 + n_y*xdim4_field_summary_kernel*1*1 + n_z*xdim4_field_summary_kernel*ydim4_field_summary_kernel*1,
           p_a5 + n_x*1*1 + n_y*xdim5_field_summary_kernel*1*1 + n_z*xdim5_field_summary_kernel*ydim5_field_summary_kernel*1,
           p_a6 + n_x*1*1 + n_y*xdim6_field_summary_kernel*1*1 + n_z*xdim6_field_summary_kernel*ydim6_field_summary_kernel*1,
           &p_a7_l,
           &p_a8_l,
           &p_a9_l,
           &p_a10_l,
           &p_a11_l );

      }
    }
  }
  *p_a7 = p_a7_l;
  *p_a8 = p_a8_l;
  *p_a9 = p_a9_l;
  *p_a10 = p_a10_l;
  *p_a11 = p_a11_l;
}

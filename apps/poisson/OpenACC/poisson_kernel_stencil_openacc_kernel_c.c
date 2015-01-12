//
// auto-generated by ops.py
//
#include "./OpenACC/poisson_common.h"

#define OPS_GPU

int xdim0_poisson_kernel_stencil;
int xdim1_poisson_kernel_stencil;
int xdim2_poisson_kernel_stencil;

#define OPS_ACC0(x,y) (x+xdim0_poisson_kernel_stencil*(y))
#define OPS_ACC1(x,y) (x+xdim1_poisson_kernel_stencil*(y))
#define OPS_ACC2(x,y) (x+xdim2_poisson_kernel_stencil*(y))

//user function
inline 
void poisson_kernel_stencil(const double *u, const double *f, double *u2) {
  u2[OPS_ACC2(0,0)] = ((u[OPS_ACC0(-1,0)]+u[OPS_ACC0(1,0)])*dx*dx
                     + (u[OPS_ACC0(0,-1)]+u[OPS_ACC0(0,1)])*dy*dy
                     - dx*dx*dy*dy*f[OPS_ACC1(0,0)])
                     /(2.0*(dx*dx+dy*dy));
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2



void poisson_kernel_stencil_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      poisson_kernel_stencil(  p_a0 + n_x*1*1 + n_y*xdim0_poisson_kernel_stencil*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_poisson_kernel_stencil*1*1, p_a2 + n_x*1*1 + n_y*xdim2_poisson_kernel_stencil*1*1 );

    }
  }
}

//
// auto-generated by ops.py
//
#include "./OpenACC/mgrid_common.h"

#define OPS_GPU

int xdim0_mgrid_populate_kernel_1;


#undef OPS_ACC0


#define OPS_ACC0(x,y) (x+xdim0_mgrid_populate_kernel_1*(y))

//user function
inline
void mgrid_populate_kernel_1(double *val, int *idx) {
  val[OPS_ACC0(0,0)] = (double)(idx[0]+6*idx[1]);
}


#undef OPS_ACC0



void mgrid_populate_kernel_1_c_wrapper(
  double *p_a0,
  int *p_a1,
  int arg_idx0, int arg_idx1,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      int arg_idx[] = {arg_idx0+n_x, arg_idx1+n_y};
      mgrid_populate_kernel_1(  p_a0 + n_x*1*1 + n_y*xdim0_mgrid_populate_kernel_1*1*1,
          arg_idx );

    }
  }
}

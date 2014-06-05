//
// auto-generated by ops.py on 2014-06-05 14:01
//


#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;
#define OPS_ACC0(x,y) (x+xdim0_advec_cell_kernel2_ydir*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_cell_kernel2_ydir*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_cell_kernel2_ydir*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_cell_kernel2_ydir*(y))


//user function
inline void advec_cell_kernel2_ydir( __global double *pre_vol, __global double *post_vol, __global double *volume, 
__global double *vol_flux_y, 
  int xdim0_advec_cell_kernel2_ydir,
int xdim1_advec_cell_kernel2_ydir,
int xdim2_advec_cell_kernel2_ydir,
int xdim3_advec_cell_kernel2_ydir)

  {

  pre_vol[OPS_ACC0(0,0)] = volume[OPS_ACC2(0,0)] + vol_flux_y[OPS_ACC3(0,1)] - vol_flux_y[OPS_ACC3(0,0)];
  post_vol[OPS_ACC1(0,0)] = volume[OPS_ACC2(0,0)];

}



 #undef OPS_ACC0
 #undef OPS_ACC1
 #undef OPS_ACC2
 #undef OPS_ACC3


 __kernel void ops_advec_cell_kernel2_ydir(
 __global double* arg0,
 __global double* arg1,
 __global double* arg2,
 __global double* arg3,
 int xdim0_advec_cell_kernel2_ydir,
 int xdim1_advec_cell_kernel2_ydir,
 int xdim2_advec_cell_kernel2_ydir,
 int xdim3_advec_cell_kernel2_ydir,
 const int base0,
 const int base1,
 const int base2,
 const int base3,
 int size0,
 int size1 ){


   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1) {
     advec_cell_kernel2_ydir(&arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_advec_cell_kernel2_ydir],
                       &arg1[base1 + idx_x * 1 + idx_y * 1 * xdim1_advec_cell_kernel2_ydir],
                       &arg2[base2 + idx_x * 1 + idx_y * 1 * xdim2_advec_cell_kernel2_ydir],
                       &arg3[base3 + idx_x * 1 + idx_y * 1 * xdim3_advec_cell_kernel2_ydir],
                       
                       xdim0_advec_cell_kernel2_ydir,
                       xdim1_advec_cell_kernel2_ydir,
                       xdim2_advec_cell_kernel2_ydir,
                       xdim3_advec_cell_kernel2_ydir);
   }

 }

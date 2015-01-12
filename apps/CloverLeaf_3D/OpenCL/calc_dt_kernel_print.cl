//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
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
#define OPS_ACC0(x,y,z) (x+xdim0_calc_dt_kernel_print*(y)+xdim0_calc_dt_kernel_print*ydim0_calc_dt_kernel_print*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_calc_dt_kernel_print*(y)+xdim1_calc_dt_kernel_print*ydim1_calc_dt_kernel_print*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_calc_dt_kernel_print*(y)+xdim2_calc_dt_kernel_print*ydim2_calc_dt_kernel_print*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_calc_dt_kernel_print*(y)+xdim3_calc_dt_kernel_print*ydim3_calc_dt_kernel_print*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_calc_dt_kernel_print*(y)+xdim4_calc_dt_kernel_print*ydim4_calc_dt_kernel_print*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_calc_dt_kernel_print*(y)+xdim5_calc_dt_kernel_print*ydim5_calc_dt_kernel_print*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_calc_dt_kernel_print*(y)+xdim6_calc_dt_kernel_print*ydim6_calc_dt_kernel_print*(z))


//user function
void calc_dt_kernel_print(const __global double * restrict xvel0, const __global double * restrict yvel0, const __global double * restrict zvel0, 
const __global double * restrict density0, const __global double * restrict energy0, const __global double * restrict pressure, const __global double * restrict soundspeed, 
 double * restrict output)

 {
  output[0] = xvel0[OPS_ACC0(0,0,0)];
  output[1] = yvel0[OPS_ACC1(0,0,0)];
  output[2] = zvel0[OPS_ACC2(0,0,0)];
  output[3] = xvel0[OPS_ACC0(1,0,0)];
  output[4] = yvel0[OPS_ACC1(1,0,0)];
  output[5] = zvel0[OPS_ACC2(0,0,0)];
  output[6] = xvel0[OPS_ACC0(1,1,0)];
  output[7] = yvel0[OPS_ACC1(1,1,0)];
  output[8] = zvel0[OPS_ACC2(0,0,0)];
  output[9] = xvel0[OPS_ACC0(0,1,0)];
  output[10] = yvel0[OPS_ACC1(0,1,0)];
  output[11] = zvel0[OPS_ACC2(0,0,0)];
  output[12] = xvel0[OPS_ACC0(0,0,1)];
  output[13] = yvel0[OPS_ACC1(0,0,1)];
  output[14] = zvel0[OPS_ACC2(0,0,1)];
  output[15] = xvel0[OPS_ACC0(1,0,1)];
  output[16] = yvel0[OPS_ACC1(1,0,1)];
  output[17] = zvel0[OPS_ACC2(0,0,1)];
  output[18] = xvel0[OPS_ACC0(1,1,1)];
  output[19] = yvel0[OPS_ACC1(1,1,1)];
  output[20] = zvel0[OPS_ACC2(0,0,1)];
  output[21] = xvel0[OPS_ACC0(0,1,1)];
  output[22] = yvel0[OPS_ACC1(0,1,1)];
  output[23] = zvel0[OPS_ACC2(0,0,1)];
  output[24] = density0[OPS_ACC3(0,0,0)];
  output[25] = energy0[OPS_ACC4(0,0,0)];
  output[26] = pressure[OPS_ACC5(0,0,0)];
  output[27] = soundspeed[OPS_ACC6(0,0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6



__kernel void ops_calc_dt_kernel_print(
__global const double* restrict arg0,
__global const double* restrict arg1,
__global const double* restrict arg2,
__global const double* restrict arg3,
__global const double* restrict arg4,
__global const double* restrict arg5,
__global const double* restrict arg6,
__global double* restrict arg7,
__local double* scratch7,
int r_bytes7,
const int base0,
const int base1,
const int base2,
const int base3,
const int base4,
const int base5,
const int base6,
const int size0,
const int size1,
const int size2 ){

  arg7 += r_bytes7;
  double arg7_l[28];
  for (int d=0; d<28; d++) arg7_l[d] = ZERO_double;

  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    calc_dt_kernel_print(&arg0[base0 + idx_x * 1*1 + idx_y * 1*1 * xdim0_calc_dt_kernel_print + idx_z * 1*1 * xdim0_calc_dt_kernel_print * ydim0_calc_dt_kernel_print],
                   &arg1[base1 + idx_x * 1*1 + idx_y * 1*1 * xdim1_calc_dt_kernel_print + idx_z * 1*1 * xdim1_calc_dt_kernel_print * ydim1_calc_dt_kernel_print],
                   &arg2[base2 + idx_x * 1*1 + idx_y * 1*1 * xdim2_calc_dt_kernel_print + idx_z * 1*1 * xdim2_calc_dt_kernel_print * ydim2_calc_dt_kernel_print],
                   &arg3[base3 + idx_x * 1*1 + idx_y * 1*1 * xdim3_calc_dt_kernel_print + idx_z * 1*1 * xdim3_calc_dt_kernel_print * ydim3_calc_dt_kernel_print],
                   &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_calc_dt_kernel_print + idx_z * 1*1 * xdim4_calc_dt_kernel_print * ydim4_calc_dt_kernel_print],
                   &arg5[base5 + idx_x * 1*1 + idx_y * 1*1 * xdim5_calc_dt_kernel_print + idx_z * 1*1 * xdim5_calc_dt_kernel_print * ydim5_calc_dt_kernel_print],
                   &arg6[base6 + idx_x * 1*1 + idx_y * 1*1 * xdim6_calc_dt_kernel_print + idx_z * 1*1 * xdim6_calc_dt_kernel_print * ydim6_calc_dt_kernel_print],
                   arg7_l);
  }
  reduce_double(arg7_l[0], scratch7, arg7, OPS_INC);

}

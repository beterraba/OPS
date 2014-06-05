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
#define OPS_ACC0(x,y) (x+xdim0_calc_dt_kernel_print*(y))
#define OPS_ACC1(x,y) (x+xdim1_calc_dt_kernel_print*(y))
#define OPS_ACC2(x,y) (x+xdim2_calc_dt_kernel_print*(y))
#define OPS_ACC3(x,y) (x+xdim3_calc_dt_kernel_print*(y))
#define OPS_ACC4(x,y) (x+xdim4_calc_dt_kernel_print*(y))
#define OPS_ACC5(x,y) (x+xdim5_calc_dt_kernel_print*(y))


//user function
void calc_dt_kernel_print( __global double *xvel0, __global double *yvel0, __global double *density0, 
__global double *energy0, __global double *pressure, __global double *soundspeed, 
  int xdim0_calc_dt_kernel_print,
int xdim1_calc_dt_kernel_print,
int xdim2_calc_dt_kernel_print,
int xdim3_calc_dt_kernel_print,
int xdim4_calc_dt_kernel_print,
int xdim5_calc_dt_kernel_print)

  {
  printf("Cell velocities:\n");
  printf("%E, %E \n",xvel0[OPS_ACC0(1,0)], yvel0[OPS_ACC1(1,0)]);
  printf("%E, %E \n",xvel0[OPS_ACC0(-1,0)], yvel0[OPS_ACC1(-1,0)]);
  printf("%E, %E \n",xvel0[OPS_ACC0(0,1)], yvel0[OPS_ACC1(0,1)]);
  printf("%E, %E \n",xvel0[OPS_ACC0(0,-1)], yvel0[OPS_ACC1(0,-1)]);

  printf("density, energy, pressure, soundspeed = %lf, %lf, %lf, %lf \n",
    density0[OPS_ACC2(0,0)], energy0[OPS_ACC3(0,0)], pressure[OPS_ACC4(0,0)], soundspeed[OPS_ACC5(0,0)]);
}



 #undef OPS_ACC0
 #undef OPS_ACC1
 #undef OPS_ACC2
 #undef OPS_ACC3
 #undef OPS_ACC4
 #undef OPS_ACC5


 __kernel void ops_calc_dt_kernel_print(
 __global double* arg0,
 __global double* arg1,
 __global double* arg2,
 __global double* arg3,
 __global double* arg4,
 __global double* arg5,
 int xdim0_calc_dt_kernel_print,
 int xdim1_calc_dt_kernel_print,
 int xdim2_calc_dt_kernel_print,
 int xdim3_calc_dt_kernel_print,
 int xdim4_calc_dt_kernel_print,
 int xdim5_calc_dt_kernel_print,
 const int base0,
 const int base1,
 const int base2,
 const int base3,
 const int base4,
 const int base5,
 int size0,
 int size1 ){


   int idx_y = get_global_id(1);
   int idx_x = get_global_id(0);

   if (idx_x < size0 && idx_y < size1) {
     calc_dt_kernel_print(&arg0[base0 + idx_x * 1 + idx_y * 1 * xdim0_calc_dt_kernel_print],
                    &arg1[base1 + idx_x * 1 + idx_y * 1 * xdim1_calc_dt_kernel_print],
                    &arg2[base2 + idx_x * 1 + idx_y * 1 * xdim2_calc_dt_kernel_print],
                    &arg3[base3 + idx_x * 1 + idx_y * 1 * xdim3_calc_dt_kernel_print],
                    &arg4[base4 + idx_x * 1 + idx_y * 1 * xdim4_calc_dt_kernel_print],
                    &arg5[base5 + idx_x * 1 + idx_y * 1 * xdim5_calc_dt_kernel_print],
                    
                    xdim0_calc_dt_kernel_print,
                    xdim1_calc_dt_kernel_print,
                    xdim2_calc_dt_kernel_print,
                    xdim3_calc_dt_kernel_print,
                    xdim4_calc_dt_kernel_print,
                    xdim5_calc_dt_kernel_print);
   }

 }

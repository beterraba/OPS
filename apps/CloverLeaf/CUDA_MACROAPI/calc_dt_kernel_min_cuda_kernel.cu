//
// auto-generated by ops.py on 2013-11-15 14:42
//

//user function
#include "calc_dt_kernel.h"

__global__ void ops_calc_dt_kernel_min(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1 ){

  double arg1_l[1];
  for (int d=0; d<1; d++) arg1_l[d] = INFINITY_double;

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_device;

  if (idx_x < size0 && idx_y < size1) {
    calc_dt_kernel_min(arg0, arg1_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction<OPS_MIN>(&arg1[d+blockIdx.x + blockIdx.y*gridDim.x],arg1_l[d]);

}

// host stub function
void ops_par_loop_calc_dt_kernel_min(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];

  cudaMemcpyToSymbol( xdim0_device, &xdim0, sizeof(int) );
  cudaMemcpyToSymbol( dt_device,  &dt, sizeof(double) );
  cudaMemcpyToSymbol( g_small_device,  &g_small, sizeof(double) );
  cudaMemcpyToSymbol( g_big_device,  &g_big, sizeof(double) );
  cudaMemcpyToSymbol( dtc_safe_device,  &dtc_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtu_safe_device,  &dtu_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtv_safe_device,  &dtv_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtdiv_safe_device,  &dtdiv_safe, sizeof(double) );


  double *arg1h = (double *)arg1.data;

  int block_size = 16;
  dim3 grid( (x_size-1)/block_size+ 1, (y_size-1)/block_size + 1, 1);
  dim3 block(block_size,block_size,1);

  int nblocks = ((x_size-1)/block_size+ 1)*((y_size-1)/block_size + 1);
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg1.data)[d+b*1] = INFINITY_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);

  char *p_a[2];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 2);

  int nshared = 0;
  int nthread = block_size*block_size;

  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_min<<<grid, block, nshared >>> (  (double *)p_a[0], (double *)arg1.data_d, x_size, y_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg1h[d] = MIN(arg1h[d],((double *)arg1.data)[d+b*1]);
    }
  }
  arg1.data = (char *)arg1h;

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 2);
}
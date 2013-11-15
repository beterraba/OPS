//
// auto-generated by ops.py on 2013-11-15 10:36
//

//user function
#include "initialise_chunk_kernel.h"

__global__ void ops_initialise_chunk_kernel_volume(
double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
const double* __restrict arg3,
double* __restrict arg4,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_device;
  arg1 += idx_x * 0 + idx_y * 1 * xdim1_device;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_device;
  arg3 += idx_x * 1 + idx_y * 0 * xdim3_device;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_device;

  if (idx_x < size0 && idx_y < size1) {
    initialise_chunk_kernel_volume(arg0, arg1, arg2, arg3,
                   arg4);
  }

}

// host stub function
void ops_par_loop_initialise_chunk_kernel_volume(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {

  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];
  int xdim4 = args[4].dat->block_size[0];

  cudaMemcpyToSymbol( xdim0_device, &xdim0, sizeof(int) );
  cudaMemcpyToSymbol( xdim1_device, &xdim1, sizeof(int) );
  cudaMemcpyToSymbol( xdim2_device, &xdim2, sizeof(int) );
  cudaMemcpyToSymbol( xdim3_device, &xdim3, sizeof(int) );
  cudaMemcpyToSymbol( xdim4_device, &xdim4, sizeof(int) );
  cudaMemcpyToSymbol( dt_device,  &dt, sizeof(double) );
  cudaMemcpyToSymbol( g_small_device,  &g_small, sizeof(double) );
  cudaMemcpyToSymbol( g_big_device,  &g_big, sizeof(double) );
  cudaMemcpyToSymbol( dtc_safe_device,  &dtc_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtu_safe_device,  &dtu_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtv_safe_device,  &dtv_safe, sizeof(double) );
  cudaMemcpyToSymbol( dtdiv_safe_device,  &dtdiv_safe, sizeof(double) );



  int block_size = 16;
  dim3 grid( (x_size-1)/block_size+ 1, (y_size-1)/block_size + 1, 1);
  dim3 block(block_size,block_size,1);




  char *p_a[5];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 0 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 0 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];

  p_a[4] = &args[4].data_d[
  + args[4].dat->size * args[4].dat->block_size[0] * ( range[2] * 1 - args[4].dat->offset[1] )
  + args[4].dat->size * ( range[0] * 1 - args[4].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 5);


  //call kernel wrapper function, passing in pointers to data
  ops_initialise_chunk_kernel_volume<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4],x_size, y_size);

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 5);
}

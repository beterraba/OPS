//
// auto-generated by ops.py on 2013-11-15 10:36
//

//user function
#include "initialise_chunk_kernel.h"

__global__ void ops_initialise_chunk_kernel_y(
double* __restrict arg0,
const int* __restrict arg1,
double* __restrict arg2,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_device;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_device;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_device;

  if (idx_x < size0 && idx_y < size1) {
    initialise_chunk_kernel_y(arg0, arg1, arg2);
  }

}

// host stub function
void ops_par_loop_initialise_chunk_kernel_y(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];

  cudaMemcpyToSymbol( xdim0_device, &xdim0, sizeof(int) );
  cudaMemcpyToSymbol( xdim1_device, &xdim1, sizeof(int) );
  cudaMemcpyToSymbol( xdim2_device, &xdim2, sizeof(int) );
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




  char *p_a[3];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];


  ops_halo_exchanges_cuda(args, 3);


  //call kernel wrapper function, passing in pointers to data
  ops_initialise_chunk_kernel_y<<<grid, block >>> (  (double *)p_a[0], (int *)p_a[1],
           (double *)p_a[2],x_size, y_size);

  cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 3);
}

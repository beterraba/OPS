//
// auto-generated by ops.py on 2014-05-23 16:24
//

__constant__ int xdim0_calc_dt_kernel_get;
__constant__ int ydim0_calc_dt_kernel_get;
__constant__ int xdim1_calc_dt_kernel_get;
__constant__ int ydim1_calc_dt_kernel_get;
__constant__ int xdim4_calc_dt_kernel_get;
__constant__ int ydim4_calc_dt_kernel_get;

#define OPS_ACC0(x,y,z) (x+xdim0_calc_dt_kernel_get*(y)+xdim0_calc_dt_kernel_get*ydim0_calc_dt_kernel_get*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_calc_dt_kernel_get*(y)+xdim1_calc_dt_kernel_get*ydim1_calc_dt_kernel_get*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_calc_dt_kernel_get*(y)+xdim4_calc_dt_kernel_get*ydim4_calc_dt_kernel_get*(z))

//user function
__device__

void calc_dt_kernel_get(const double* cellx, const double* celly, double* xl_pos, double* yl_pos, const double *cellz, double *zl_pos) {
  *xl_pos = cellx[OPS_ACC0(0,0,0)];
  *yl_pos = celly[OPS_ACC1(0,0,0)];
  *zl_pos = cellz[OPS_ACC4(0,0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC4


__global__ void ops_calc_dt_kernel_get(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
const double* __restrict arg4,
double* __restrict arg5,
int size0,
int size1,
int size2 ){

  double arg2_l[1];
  double arg3_l[1];
  double arg5_l[1];
  for (int d=0; d<1; d++) arg2_l[d] = ZERO_double;
  for (int d=0; d<1; d++) arg3_l[d] = ZERO_double;
  for (int d=0; d<1; d++) arg5_l[d] = ZERO_double;

  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 0 * xdim0_calc_dt_kernel_get + idx_z * 0 * xdim0_calc_dt_kernel_get * ydim0_calc_dt_kernel_get;
  arg1 += idx_x * 0 + idx_y * 1 * xdim1_calc_dt_kernel_get + idx_z * 0 * xdim1_calc_dt_kernel_get * ydim1_calc_dt_kernel_get;
  arg4 += idx_x * 0 + idx_y * 0 * xdim4_calc_dt_kernel_get + idx_z * 1 * xdim4_calc_dt_kernel_get * ydim4_calc_dt_kernel_get;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    calc_dt_kernel_get(arg0, arg1, arg2_l, arg3_l,
                   arg4, arg5_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction<OPS_INC>(&arg2[d+blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y],arg2_l[d]);
  for (int d=0; d<1; d++)
    ops_reduction<OPS_INC>(&arg3[d+blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y],arg3_l[d]);
  for (int d=0; d<1; d++)
    ops_reduction<OPS_INC>(&arg5[d+blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y],arg5_l[d]);

}

// host stub function
void ops_par_loop_calc_dt_kernel_get(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5) {

  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->block_size[1];
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  int ydim1 = args[1].dat->block_size[1];
  int xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  int ydim4 = args[4].dat->block_size[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(39,"calc_dt_kernel_get");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[39].count == 0) {
    cudaMemcpyToSymbol( xdim0_calc_dt_kernel_get, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( ydim0_calc_dt_kernel_get, &ydim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_calc_dt_kernel_get, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( ydim1_calc_dt_kernel_get, &ydim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_calc_dt_kernel_get, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( ydim4_calc_dt_kernel_get, &ydim4, sizeof(int) );
  }


  double *arg2h = (double *)arg2.data;
  double *arg3h = (double *)arg3.data;
  double *arg5h = (double *)arg5.data;

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1)*z_size;
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg2.data = OPS_reduct_h + reduct_bytes;
  arg2.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg2.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));

  arg3.data = OPS_reduct_h + reduct_bytes;
  arg3.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg3.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));

  arg5.data = OPS_reduct_h + reduct_bytes;
  arg5.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg5.data)[d+b*1] = ZERO_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat4 = args[4].dat->size;

  char *p_a[6];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = dat1 * 1 * 
  (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base4 = dat4 * 1 * 
  (start_add[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start_add[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    args[4].dat->block_size[1] *
    (start_add[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);
  p_a[4] = (char *)args[4].data_d + base4;


  ops_H_D_exchanges_cuda(args, 6);
  ops_halo_exchanges(args,6,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[39].mpi_time += t1-t2;

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y;

  nshared = MAX(nshared,sizeof(double)*1);
  nshared = MAX(nshared,sizeof(double)*1);
  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_get<<<grid, block, nshared >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)arg2.data_d, (double *)arg3.data_d,
           (double *)p_a[4], (double *)arg5.data_d,x_size, y_size, z_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg2h[d] = arg2h[d] + ((double *)arg2.data)[d+b*1];
    }
  }
  arg2.data = (char *)arg2h;

  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg3h[d] = arg3h[d] + ((double *)arg3.data)[d+b*1];
    }
  }
  arg3.data = (char *)arg3h;

  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg5h[d] = arg5h[d] + ((double *)arg5.data)[d+b*1];
    }
  }
  arg5.data = (char *)arg5h;

  if (OPS_diags>1) cutilSafeCall(cudaDeviceSynchronize());
  ops_timers_core(&c2,&t2);
  OPS_kernels[39].time += t2-t1;
  ops_mpi_reduce(&arg2,(double *)p_a[2]);
  ops_mpi_reduce(&arg3,(double *)p_a[3]);
  ops_mpi_reduce(&arg5,(double *)p_a[5]);
  ops_timers_core(&c1,&t1);
  OPS_kernels[39].mpi_time += t1-t2;
  ops_set_dirtybit_cuda(args, 6);

  //Update kernel record
  OPS_kernels[39].count++;
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[39].transfer += ops_compute_transfer(dim, range, &arg4);
}

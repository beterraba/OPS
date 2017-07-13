//
// auto-generated by ops.py
//
__constant__ int xdim0_advec_mom_kernel2_y;
int xdim0_advec_mom_kernel2_y_h = -1;
int ydim0_advec_mom_kernel2_y_h = -1;
__constant__ int xdim1_advec_mom_kernel2_y;
int xdim1_advec_mom_kernel2_y_h = -1;
int ydim1_advec_mom_kernel2_y_h = -1;
__constant__ int xdim2_advec_mom_kernel2_y;
int xdim2_advec_mom_kernel2_y_h = -1;
int ydim2_advec_mom_kernel2_y_h = -1;
__constant__ int xdim3_advec_mom_kernel2_y;
int xdim3_advec_mom_kernel2_y_h = -1;
int ydim3_advec_mom_kernel2_y_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


#define OPS_ACC0(x,y) (x+xdim0_advec_mom_kernel2_y*(y))
#define OPS_ACC1(x,y) (x+xdim1_advec_mom_kernel2_y*(y))
#define OPS_ACC2(x,y) (x+xdim2_advec_mom_kernel2_y*(y))
#define OPS_ACC3(x,y) (x+xdim3_advec_mom_kernel2_y*(y))

//user function
__device__

inline void advec_mom_kernel2_y_gpu( double *vel1, const double *node_mass_post,
                        const double *node_mass_pre, const double *mom_flux) {

  vel1[OPS_ACC0(0,0)] = ( vel1[OPS_ACC0(0,0)] * node_mass_pre[OPS_ACC2(0,0)]  +
    mom_flux[OPS_ACC3(0,-1)] - mom_flux[OPS_ACC3(0,0)] ) / node_mass_post[OPS_ACC1(0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


__global__ void ops_advec_mom_kernel2_y(
double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_advec_mom_kernel2_y;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_advec_mom_kernel2_y;
  arg2 += idx_x * 1*1 + idx_y * 1*1 * xdim2_advec_mom_kernel2_y;
  arg3 += idx_x * 1*1 + idx_y * 1*1 * xdim3_advec_mom_kernel2_y;

  if (idx_x < size0 && idx_y < size1) {
    advec_mom_kernel2_y_gpu(arg0, arg1, arg2, arg3);
  }

}

// host stub function
// host stub function
void ops_par_loop_advec_mom_kernel2_y_execute(ops_kernel_descriptor *desc) {
  #ifdef OPS_MPI
  ops_block block = desc->block;
  #endif
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,4,range,26)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(26,"advec_mom_kernel2_y");
    OPS_kernels[26].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }


  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];

  if (xdim0 != xdim0_advec_mom_kernel2_y_h || xdim1 != xdim1_advec_mom_kernel2_y_h || xdim2 != xdim2_advec_mom_kernel2_y_h || xdim3 != xdim3_advec_mom_kernel2_y_h) {
    cudaMemcpyToSymbolAsync( xdim0_advec_mom_kernel2_y, &xdim0, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim0_advec_mom_kernel2_y_h = xdim0;
    cudaMemcpyToSymbolAsync( xdim1_advec_mom_kernel2_y, &xdim1, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim1_advec_mom_kernel2_y_h = xdim1;
    cudaMemcpyToSymbolAsync( xdim2_advec_mom_kernel2_y, &xdim2, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim2_advec_mom_kernel2_y_h = xdim2;
    cudaMemcpyToSymbolAsync( xdim3_advec_mom_kernel2_y, &xdim3, sizeof(int),0,cudaMemcpyHostToDevice,stream );
    xdim3_advec_mom_kernel2_y_h = xdim3;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[4];
  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;

  //set up initial pointers
  int base0 = args[0].dat->base_offset;
  base0 += dat0 * (start[0] * args[0].stencil->stride[0]);
  base0 += dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].dat->data_d + base0;

  int base1 = args[1].dat->base_offset;
  base1 += dat1 * (start[0] * args[1].stencil->stride[0]);
  base1 += dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].dat->data_d + base1;

  int base2 = args[2].dat->base_offset;
  base2 += dat2 * (start[0] * args[2].stencil->stride[0]);
  base2 += dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].dat->data_d + base2;

  int base3 = args[3].dat->base_offset;
  base3 += dat3 * (start[0] * args[3].stencil->stride[0]);
  base3 += dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].dat->data_d + base3;


  ops_H_D_exchanges_device(args, 4);
  ops_halo_exchanges(args,4,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[26].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_advec_mom_kernel2_y<<<grid, tblock, 0, stream >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],x_size, y_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaStreamSynchronize(stream));
    ops_timers_core(&c1,&t1);
    OPS_kernels[26].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 4);
  ops_set_halo_dirtybit3(&args[0],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[26].mpi_time += t2-t1;
    OPS_kernels[26].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[26].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[26].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[26].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}

void ops_par_loop_advec_mom_kernel2_y(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 26;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 26;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->function = ops_par_loop_advec_mom_kernel2_y_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(26,"advec_mom_kernel2_y");
  }
  ops_enqueue_kernel(desc);
}

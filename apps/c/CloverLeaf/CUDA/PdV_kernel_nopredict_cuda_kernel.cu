//
// auto-generated by ops.py
//
__constant__ int xdim0_PdV_kernel_nopredict;
int xdim0_PdV_kernel_nopredict_h = -1;
int ydim0_PdV_kernel_nopredict_h = -1;
__constant__ int xdim1_PdV_kernel_nopredict;
int xdim1_PdV_kernel_nopredict_h = -1;
int ydim1_PdV_kernel_nopredict_h = -1;
__constant__ int xdim2_PdV_kernel_nopredict;
int xdim2_PdV_kernel_nopredict_h = -1;
int ydim2_PdV_kernel_nopredict_h = -1;
__constant__ int xdim3_PdV_kernel_nopredict;
int xdim3_PdV_kernel_nopredict_h = -1;
int ydim3_PdV_kernel_nopredict_h = -1;
__constant__ int xdim4_PdV_kernel_nopredict;
int xdim4_PdV_kernel_nopredict_h = -1;
int ydim4_PdV_kernel_nopredict_h = -1;
__constant__ int xdim5_PdV_kernel_nopredict;
int xdim5_PdV_kernel_nopredict_h = -1;
int ydim5_PdV_kernel_nopredict_h = -1;
__constant__ int xdim6_PdV_kernel_nopredict;
int xdim6_PdV_kernel_nopredict_h = -1;
int ydim6_PdV_kernel_nopredict_h = -1;
__constant__ int xdim7_PdV_kernel_nopredict;
int xdim7_PdV_kernel_nopredict_h = -1;
int ydim7_PdV_kernel_nopredict_h = -1;
__constant__ int xdim8_PdV_kernel_nopredict;
int xdim8_PdV_kernel_nopredict_h = -1;
int ydim8_PdV_kernel_nopredict_h = -1;
__constant__ int xdim9_PdV_kernel_nopredict;
int xdim9_PdV_kernel_nopredict_h = -1;
int ydim9_PdV_kernel_nopredict_h = -1;
__constant__ int xdim10_PdV_kernel_nopredict;
int xdim10_PdV_kernel_nopredict_h = -1;
int ydim10_PdV_kernel_nopredict_h = -1;
__constant__ int xdim11_PdV_kernel_nopredict;
int xdim11_PdV_kernel_nopredict_h = -1;
int ydim11_PdV_kernel_nopredict_h = -1;
__constant__ int xdim12_PdV_kernel_nopredict;
int xdim12_PdV_kernel_nopredict_h = -1;
int ydim12_PdV_kernel_nopredict_h = -1;
__constant__ int xdim13_PdV_kernel_nopredict;
int xdim13_PdV_kernel_nopredict_h = -1;
int ydim13_PdV_kernel_nopredict_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10
#undef OPS_ACC11
#undef OPS_ACC12
#undef OPS_ACC13


#define OPS_ACC0(x,y) (x+xdim0_PdV_kernel_nopredict*(y))
#define OPS_ACC1(x,y) (x+xdim1_PdV_kernel_nopredict*(y))
#define OPS_ACC2(x,y) (x+xdim2_PdV_kernel_nopredict*(y))
#define OPS_ACC3(x,y) (x+xdim3_PdV_kernel_nopredict*(y))
#define OPS_ACC4(x,y) (x+xdim4_PdV_kernel_nopredict*(y))
#define OPS_ACC5(x,y) (x+xdim5_PdV_kernel_nopredict*(y))
#define OPS_ACC6(x,y) (x+xdim6_PdV_kernel_nopredict*(y))
#define OPS_ACC7(x,y) (x+xdim7_PdV_kernel_nopredict*(y))
#define OPS_ACC8(x,y) (x+xdim8_PdV_kernel_nopredict*(y))
#define OPS_ACC9(x,y) (x+xdim9_PdV_kernel_nopredict*(y))
#define OPS_ACC10(x,y) (x+xdim10_PdV_kernel_nopredict*(y))
#define OPS_ACC11(x,y) (x+xdim11_PdV_kernel_nopredict*(y))
#define OPS_ACC12(x,y) (x+xdim12_PdV_kernel_nopredict*(y))
#define OPS_ACC13(x,y) (x+xdim13_PdV_kernel_nopredict*(y))

//user function
__device__

void PdV_kernel_nopredict_gpu(const double *xarea, const double *xvel0, const double *xvel1,
                const double *yarea, const double *yvel0, const double *yvel1,
                double *volume_change, const double *volume,
                const double *pressure,
                const double *density0, double *density1,
                const double *viscosity,
                const double *energy0, double *energy1) {


  double recip_volume, energy_change;
  double right_flux, left_flux, top_flux, bottom_flux, total_flux;

  left_flux = ( xarea[OPS_ACC0(0,0)] * ( xvel0[OPS_ACC1(0,0)] + xvel0[OPS_ACC1(0,1)] +
                                xvel1[OPS_ACC2(0,0)] + xvel1[OPS_ACC2(0,1)] ) ) * 0.25 * dt;
  right_flux = ( xarea[OPS_ACC0(1,0)] * ( xvel0[OPS_ACC1(1,0)] + xvel0[OPS_ACC1(1,1)] +
                                 xvel1[OPS_ACC2(1,0)] + xvel1[OPS_ACC2(1,1)] ) ) * 0.25 * dt;

  bottom_flux = ( yarea[OPS_ACC3(0,0)] * ( yvel0[OPS_ACC4(0,0)] + yvel0[OPS_ACC4(1,0)] +
                                  yvel1[OPS_ACC5(0,0)] + yvel1[OPS_ACC5(1,0)] ) ) * 0.25* dt;
  top_flux = ( yarea[OPS_ACC3(0,1)] * ( yvel0[OPS_ACC4(0,1)] + yvel0[OPS_ACC4(1,1)] +
                               yvel1[OPS_ACC5(0,1)] + yvel1[OPS_ACC5(1,1)] ) ) * 0.25 * dt;

  total_flux = right_flux - left_flux + top_flux - bottom_flux;

  volume_change[OPS_ACC6(0,0)] = (volume[OPS_ACC7(0,0)])/(volume[OPS_ACC7(0,0)] + total_flux);




  recip_volume = 1.0/volume[OPS_ACC7(0,0)];

  energy_change = ( pressure[OPS_ACC8(0,0)]/density0[OPS_ACC9(0,0)] +
                    viscosity[OPS_ACC11(0,0)]/density0[OPS_ACC9(0,0)] ) * total_flux * recip_volume;
  energy1[OPS_ACC13(0,0)] = energy0[OPS_ACC12(0,0)] - energy_change;
  density1[OPS_ACC10(0,0)] = density0[OPS_ACC9(0,0)] * volume_change[OPS_ACC6(0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10
#undef OPS_ACC11
#undef OPS_ACC12
#undef OPS_ACC13


__global__ void ops_PdV_kernel_nopredict(
const double* __restrict arg0,
const double* __restrict arg1,
const double* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
const double* __restrict arg7,
const double* __restrict arg8,
const double* __restrict arg9,
double* __restrict arg10,
const double* __restrict arg11,
const double* __restrict arg12,
double* __restrict arg13,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1 + idx_y * 1*1 * xdim0_PdV_kernel_nopredict;
  arg1 += idx_x * 1*1 + idx_y * 1*1 * xdim1_PdV_kernel_nopredict;
  arg2 += idx_x * 1*1 + idx_y * 1*1 * xdim2_PdV_kernel_nopredict;
  arg3 += idx_x * 1*1 + idx_y * 1*1 * xdim3_PdV_kernel_nopredict;
  arg4 += idx_x * 1*1 + idx_y * 1*1 * xdim4_PdV_kernel_nopredict;
  arg5 += idx_x * 1*1 + idx_y * 1*1 * xdim5_PdV_kernel_nopredict;
  arg6 += idx_x * 1*1 + idx_y * 1*1 * xdim6_PdV_kernel_nopredict;
  arg7 += idx_x * 1*1 + idx_y * 1*1 * xdim7_PdV_kernel_nopredict;
  arg8 += idx_x * 1*1 + idx_y * 1*1 * xdim8_PdV_kernel_nopredict;
  arg9 += idx_x * 1*1 + idx_y * 1*1 * xdim9_PdV_kernel_nopredict;
  arg10 += idx_x * 1*1 + idx_y * 1*1 * xdim10_PdV_kernel_nopredict;
  arg11 += idx_x * 1*1 + idx_y * 1*1 * xdim11_PdV_kernel_nopredict;
  arg12 += idx_x * 1*1 + idx_y * 1*1 * xdim12_PdV_kernel_nopredict;
  arg13 += idx_x * 1*1 + idx_y * 1*1 * xdim13_PdV_kernel_nopredict;

  if (idx_x < size0 && idx_y < size1) {
    PdV_kernel_nopredict_gpu(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7, arg8,
                   arg9, arg10, arg11, arg12, arg13);
  }

}

// host stub function
void ops_par_loop_PdV_kernel_nopredict(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8,
 ops_arg arg9, ops_arg arg10, ops_arg arg11, ops_arg arg12, ops_arg arg13) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[14] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,14,range,5)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(5,"PdV_kernel_nopredict");
    OPS_kernels[5].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];
  int xdim7 = args[7].dat->size[0];
  int xdim8 = args[8].dat->size[0];
  int xdim9 = args[9].dat->size[0];
  int xdim10 = args[10].dat->size[0];
  int xdim11 = args[11].dat->size[0];
  int xdim12 = args[12].dat->size[0];
  int xdim13 = args[13].dat->size[0];

  if (xdim0 != xdim0_PdV_kernel_nopredict_h || xdim1 != xdim1_PdV_kernel_nopredict_h || xdim2 != xdim2_PdV_kernel_nopredict_h || xdim3 != xdim3_PdV_kernel_nopredict_h || xdim4 != xdim4_PdV_kernel_nopredict_h || xdim5 != xdim5_PdV_kernel_nopredict_h || xdim6 != xdim6_PdV_kernel_nopredict_h || xdim7 != xdim7_PdV_kernel_nopredict_h || xdim8 != xdim8_PdV_kernel_nopredict_h || xdim9 != xdim9_PdV_kernel_nopredict_h || xdim10 != xdim10_PdV_kernel_nopredict_h || xdim11 != xdim11_PdV_kernel_nopredict_h || xdim12 != xdim12_PdV_kernel_nopredict_h || xdim13 != xdim13_PdV_kernel_nopredict_h) {
    cudaMemcpyToSymbol( xdim0_PdV_kernel_nopredict, &xdim0, sizeof(int) );
    xdim0_PdV_kernel_nopredict_h = xdim0;
    cudaMemcpyToSymbol( xdim1_PdV_kernel_nopredict, &xdim1, sizeof(int) );
    xdim1_PdV_kernel_nopredict_h = xdim1;
    cudaMemcpyToSymbol( xdim2_PdV_kernel_nopredict, &xdim2, sizeof(int) );
    xdim2_PdV_kernel_nopredict_h = xdim2;
    cudaMemcpyToSymbol( xdim3_PdV_kernel_nopredict, &xdim3, sizeof(int) );
    xdim3_PdV_kernel_nopredict_h = xdim3;
    cudaMemcpyToSymbol( xdim4_PdV_kernel_nopredict, &xdim4, sizeof(int) );
    xdim4_PdV_kernel_nopredict_h = xdim4;
    cudaMemcpyToSymbol( xdim5_PdV_kernel_nopredict, &xdim5, sizeof(int) );
    xdim5_PdV_kernel_nopredict_h = xdim5;
    cudaMemcpyToSymbol( xdim6_PdV_kernel_nopredict, &xdim6, sizeof(int) );
    xdim6_PdV_kernel_nopredict_h = xdim6;
    cudaMemcpyToSymbol( xdim7_PdV_kernel_nopredict, &xdim7, sizeof(int) );
    xdim7_PdV_kernel_nopredict_h = xdim7;
    cudaMemcpyToSymbol( xdim8_PdV_kernel_nopredict, &xdim8, sizeof(int) );
    xdim8_PdV_kernel_nopredict_h = xdim8;
    cudaMemcpyToSymbol( xdim9_PdV_kernel_nopredict, &xdim9, sizeof(int) );
    xdim9_PdV_kernel_nopredict_h = xdim9;
    cudaMemcpyToSymbol( xdim10_PdV_kernel_nopredict, &xdim10, sizeof(int) );
    xdim10_PdV_kernel_nopredict_h = xdim10;
    cudaMemcpyToSymbol( xdim11_PdV_kernel_nopredict, &xdim11, sizeof(int) );
    xdim11_PdV_kernel_nopredict_h = xdim11;
    cudaMemcpyToSymbol( xdim12_PdV_kernel_nopredict, &xdim12, sizeof(int) );
    xdim12_PdV_kernel_nopredict_h = xdim12;
    cudaMemcpyToSymbol( xdim13_PdV_kernel_nopredict, &xdim13, sizeof(int) );
    xdim13_PdV_kernel_nopredict_h = xdim13;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;
  int dat5 = args[5].dat->elem_size;
  int dat6 = args[6].dat->elem_size;
  int dat7 = args[7].dat->elem_size;
  int dat8 = args[8].dat->elem_size;
  int dat9 = args[9].dat->elem_size;
  int dat10 = args[10].dat->elem_size;
  int dat11 = args[11].dat->elem_size;
  int dat12 = args[12].dat->elem_size;
  int dat13 = args[13].dat->elem_size;

  char *p_a[14];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
  #endif
  int base2 = dat2 * 1 *
  (start[0] * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1] - args[2].dat->base[1] - d_m[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
  #endif
  int base3 = dat3 * 1 *
  (start[0] * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
  base3 = base3+ dat3 *
    args[3].dat->size[0] *
    (start[1] * args[3].stencil->stride[1] - args[3].dat->base[1] - d_m[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
  #endif
  int base4 = dat4 * 1 *
  (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1] - args[4].dat->base[1] - d_m[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
  #endif
  int base5 = dat5 * 1 *
  (start[0] * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
  base5 = base5+ dat5 *
    args[5].dat->size[0] *
    (start[1] * args[5].stencil->stride[1] - args[5].dat->base[1] - d_m[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d];
  #endif
  int base6 = dat6 * 1 *
  (start[0] * args[6].stencil->stride[0] - args[6].dat->base[0] - d_m[0]);
  base6 = base6+ dat6 *
    args[6].dat->size[0] *
    (start[1] * args[6].stencil->stride[1] - args[6].dat->base[1] - d_m[1]);
  p_a[6] = (char *)args[6].data_d + base6;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d] + OPS_sub_dat_list[args[7].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d];
  #endif
  int base7 = dat7 * 1 *
  (start[0] * args[7].stencil->stride[0] - args[7].dat->base[0] - d_m[0]);
  base7 = base7+ dat7 *
    args[7].dat->size[0] *
    (start[1] * args[7].stencil->stride[1] - args[7].dat->base[1] - d_m[1]);
  p_a[7] = (char *)args[7].data_d + base7;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[8].dat->d_m[d] + OPS_sub_dat_list[args[8].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[8].dat->d_m[d];
  #endif
  int base8 = dat8 * 1 *
  (start[0] * args[8].stencil->stride[0] - args[8].dat->base[0] - d_m[0]);
  base8 = base8+ dat8 *
    args[8].dat->size[0] *
    (start[1] * args[8].stencil->stride[1] - args[8].dat->base[1] - d_m[1]);
  p_a[8] = (char *)args[8].data_d + base8;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[9].dat->d_m[d] + OPS_sub_dat_list[args[9].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[9].dat->d_m[d];
  #endif
  int base9 = dat9 * 1 *
  (start[0] * args[9].stencil->stride[0] - args[9].dat->base[0] - d_m[0]);
  base9 = base9+ dat9 *
    args[9].dat->size[0] *
    (start[1] * args[9].stencil->stride[1] - args[9].dat->base[1] - d_m[1]);
  p_a[9] = (char *)args[9].data_d + base9;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[10].dat->d_m[d] + OPS_sub_dat_list[args[10].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[10].dat->d_m[d];
  #endif
  int base10 = dat10 * 1 *
  (start[0] * args[10].stencil->stride[0] - args[10].dat->base[0] - d_m[0]);
  base10 = base10+ dat10 *
    args[10].dat->size[0] *
    (start[1] * args[10].stencil->stride[1] - args[10].dat->base[1] - d_m[1]);
  p_a[10] = (char *)args[10].data_d + base10;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[11].dat->d_m[d] + OPS_sub_dat_list[args[11].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[11].dat->d_m[d];
  #endif
  int base11 = dat11 * 1 *
  (start[0] * args[11].stencil->stride[0] - args[11].dat->base[0] - d_m[0]);
  base11 = base11+ dat11 *
    args[11].dat->size[0] *
    (start[1] * args[11].stencil->stride[1] - args[11].dat->base[1] - d_m[1]);
  p_a[11] = (char *)args[11].data_d + base11;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[12].dat->d_m[d] + OPS_sub_dat_list[args[12].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[12].dat->d_m[d];
  #endif
  int base12 = dat12 * 1 *
  (start[0] * args[12].stencil->stride[0] - args[12].dat->base[0] - d_m[0]);
  base12 = base12+ dat12 *
    args[12].dat->size[0] *
    (start[1] * args[12].stencil->stride[1] - args[12].dat->base[1] - d_m[1]);
  p_a[12] = (char *)args[12].data_d + base12;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[13].dat->d_m[d] + OPS_sub_dat_list[args[13].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[13].dat->d_m[d];
  #endif
  int base13 = dat13 * 1 *
  (start[0] * args[13].stencil->stride[0] - args[13].dat->base[0] - d_m[0]);
  base13 = base13+ dat13 *
    args[13].dat->size[0] *
    (start[1] * args[13].stencil->stride[1] - args[13].dat->base[1] - d_m[1]);
  p_a[13] = (char *)args[13].data_d + base13;


  ops_H_D_exchanges_device(args, 14);
  ops_halo_exchanges(args,14,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[5].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_PdV_kernel_nopredict<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],
           (double *)p_a[8], (double *)p_a[9],
           (double *)p_a[10], (double *)p_a[11],
           (double *)p_a[12], (double *)p_a[13],x_size, y_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[5].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 14);
  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[10],range);
  ops_set_halo_dirtybit3(&args[13],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[5].mpi_time += t2-t1;
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg10);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg11);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg12);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg13);
  }
}

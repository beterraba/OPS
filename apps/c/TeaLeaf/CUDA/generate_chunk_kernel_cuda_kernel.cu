//
// auto-generated by ops.py
//
__constant__ int xdim0_generate_chunk_kernel;
int xdim0_generate_chunk_kernel_h = -1;
__constant__ int xdim1_generate_chunk_kernel;
int xdim1_generate_chunk_kernel_h = -1;
__constant__ int xdim2_generate_chunk_kernel;
int xdim2_generate_chunk_kernel_h = -1;
__constant__ int xdim3_generate_chunk_kernel;
int xdim3_generate_chunk_kernel_h = -1;
__constant__ int xdim4_generate_chunk_kernel;
int xdim4_generate_chunk_kernel_h = -1;
__constant__ int xdim5_generate_chunk_kernel;
int xdim5_generate_chunk_kernel_h = -1;
__constant__ int xdim6_generate_chunk_kernel;
int xdim6_generate_chunk_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6

#define OPS_ACC0(x, y) (x + xdim0_generate_chunk_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_generate_chunk_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_generate_chunk_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_generate_chunk_kernel * (y))
#define OPS_ACC4(x, y) (x + xdim4_generate_chunk_kernel * (y))
#define OPS_ACC5(x, y) (x + xdim5_generate_chunk_kernel * (y))
#define OPS_ACC6(x, y) (x + xdim6_generate_chunk_kernel * (y))

// user function
__device__

    void
    generate_chunk_kernel_gpu(const double *vertexx, const double *vertexy,
                              double *energy0, double *density0, double *u0,
                              const double *cellx, const double *celly) {

  double radius, x_cent, y_cent;
  int is_in = 0;
  int is_in2 = 0;

  energy0[OPS_ACC2(0, 0)] = states[0].energy;
  density0[OPS_ACC3(0, 0)] = states[0].density;

  for (int i = 1; i < number_of_states; i++) {

    x_cent = states[i].xmin;
    y_cent = states[i].ymin;
    is_in = 0;
    is_in2 = 0;

    if (states[i].geometry == g_rect) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          if (vertexx[OPS_ACC0(1 + i1, 0)] >= states[i].xmin &&
              vertexx[OPS_ACC0(0 + i1, 0)] < states[i].xmax) {
            if (vertexy[OPS_ACC1(0, 1 + j1)] >= states[i].ymin &&
                vertexy[OPS_ACC1(0, 0 + j1)] < states[i].ymax) {
              is_in = 1;
            }
          }
        }
      }
      if (vertexx[OPS_ACC0(1, 0)] >= states[i].xmin &&
          vertexx[OPS_ACC0(0, 0)] < states[i].xmax) {
        if (vertexy[OPS_ACC1(0, 1)] >= states[i].ymin &&
            vertexy[OPS_ACC1(0, 0)] < states[i].ymax) {
          is_in2 = 1;
        }
      }
      if (is_in2) {
        energy0[OPS_ACC2(0, 0)] = states[i].energy;
        density0[OPS_ACC3(0, 0)] = states[i].density;
      }
    } else if (states[i].geometry == g_circ) {
      for (int i1 = -1; i1 <= 0; i1++) {
        for (int j1 = -1; j1 <= 0; j1++) {
          radius = sqrt((cellx[OPS_ACC5(i1, 0)] - x_cent) *
                            (cellx[OPS_ACC5(i1, 0)] - x_cent) +
                        (celly[OPS_ACC6(0, j1)] - y_cent) *
                            (celly[OPS_ACC6(0, j1)] - y_cent));
          if (radius <= states[i].radius) {
            is_in = 1;
          }
        }
      }
      if (radius <= states[i].radius)
        is_in2 = 1;

      if (is_in2) {
        energy0[OPS_ACC2(0, 0)] = states[i].energy;
        density0[OPS_ACC3(0, 0)] = states[i].density;
      }
    } else if (states[i].geometry == g_point) {
      if (vertexx[OPS_ACC0(0, 0)] == x_cent &&
          vertexy[OPS_ACC1(0, 0)] == y_cent) {
        energy0[OPS_ACC2(0, 0)] = states[i].energy;
        density0[OPS_ACC3(0, 0)] = states[i].density;
      }
    }
  }
  u0[OPS_ACC4(0, 0)] = energy0[OPS_ACC2(0, 0)] * density0[OPS_ACC3(0, 0)];
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6

__global__ void ops_generate_chunk_kernel(
    const double *__restrict arg0, const double *__restrict arg1,
    double *__restrict arg2, double *__restrict arg3, double *__restrict arg4,
    const double *__restrict arg5, const double *__restrict arg6, int size0,
    int size1) {

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 * 1 + idx_y * 0 * 1 * xdim0_generate_chunk_kernel;
  arg1 += idx_x * 0 * 1 + idx_y * 1 * 1 * xdim1_generate_chunk_kernel;
  arg2 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim2_generate_chunk_kernel;
  arg3 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim3_generate_chunk_kernel;
  arg4 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim4_generate_chunk_kernel;
  arg5 += idx_x * 1 * 1 + idx_y * 0 * 1 * xdim5_generate_chunk_kernel;
  arg6 += idx_x * 0 * 1 + idx_y * 1 * 1 * xdim6_generate_chunk_kernel;

  if (idx_x < size0 && idx_y < size1) {
    generate_chunk_kernel_gpu(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
  }
}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_generate_chunk_kernel(char const *name, ops_block block,
                                        int dim, int *range, ops_arg arg0,
                                        ops_arg arg1, ops_arg arg2,
                                        ops_arg arg3, ops_arg arg4,
                                        ops_arg arg5, ops_arg arg6) {
#else
void ops_par_loop_generate_chunk_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
#endif

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[7] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6};

#if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args, 7, range, 1))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(1, "generate_chunk_kernel");
    OPS_kernels[1].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 2; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];

  if (xdim0 != xdim0_generate_chunk_kernel_h ||
      xdim1 != xdim1_generate_chunk_kernel_h ||
      xdim2 != xdim2_generate_chunk_kernel_h ||
      xdim3 != xdim3_generate_chunk_kernel_h ||
      xdim4 != xdim4_generate_chunk_kernel_h ||
      xdim5 != xdim5_generate_chunk_kernel_h ||
      xdim6 != xdim6_generate_chunk_kernel_h) {
    cudaMemcpyToSymbol(xdim0_generate_chunk_kernel, &xdim0, sizeof(int));
    xdim0_generate_chunk_kernel_h = xdim0;
    cudaMemcpyToSymbol(xdim1_generate_chunk_kernel, &xdim1, sizeof(int));
    xdim1_generate_chunk_kernel_h = xdim1;
    cudaMemcpyToSymbol(xdim2_generate_chunk_kernel, &xdim2, sizeof(int));
    xdim2_generate_chunk_kernel_h = xdim2;
    cudaMemcpyToSymbol(xdim3_generate_chunk_kernel, &xdim3, sizeof(int));
    xdim3_generate_chunk_kernel_h = xdim3;
    cudaMemcpyToSymbol(xdim4_generate_chunk_kernel, &xdim4, sizeof(int));
    xdim4_generate_chunk_kernel_h = xdim4;
    cudaMemcpyToSymbol(xdim5_generate_chunk_kernel, &xdim5, sizeof(int));
    xdim5_generate_chunk_kernel_h = xdim5;
    cudaMemcpyToSymbol(xdim6_generate_chunk_kernel, &xdim6, sizeof(int));
    xdim6_generate_chunk_kernel_h = xdim6;
  }

  dim3 grid((x_size - 1) / OPS_block_size_x + 1,
            (y_size - 1) / OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x, OPS_block_size_y, 1);

  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);

  char *p_a[7];

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0 +
          dat0 * args[0].dat->size[0] * (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset +
              dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1 +
          dat1 * args[1].dat->size[0] * (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset +
              dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2 +
          dat2 * args[2].dat->size[0] * (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset +
              dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3 +
          dat3 * args[3].dat->size[0] * (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset +
              dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4 +
          dat4 * args[4].dat->size[0] * (start[1] * args[4].stencil->stride[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset +
              dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5 +
          dat5 * args[5].dat->size[0] * (start[1] * args[5].stencil->stride[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset +
              dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6 +
          dat6 * args[6].dat->size[0] * (start[1] * args[6].stencil->stride[1]);
  p_a[6] = (char *)args[6].data_d + base6;

#ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 7);
  ops_halo_exchanges(args, 7, range);
#endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[1].mpi_time += t2 - t1;
  }

  // call kernel wrapper function, passing in pointers to data
  ops_generate_chunk_kernel<<<grid, tblock>>>(
      (double *)p_a[0], (double *)p_a[1], (double *)p_a[2], (double *)p_a[3],
      (double *)p_a[4], (double *)p_a[5], (double *)p_a[6], x_size, y_size);

  if (OPS_diags > 1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1, &t1);
    OPS_kernels[1].time += t1 - t2;
  }

#ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 7);
  ops_set_halo_dirtybit3(&args[2], range);
  ops_set_halo_dirtybit3(&args[3], range);
  ops_set_halo_dirtybit3(&args[4], range);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[1].mpi_time += t2 - t1;
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_generate_chunk_kernel(char const *name, ops_block block,
                                        int dim, int *range, ops_arg arg0,
                                        ops_arg arg1, ops_arg arg2,
                                        ops_arg arg3, ops_arg arg4,
                                        ops_arg arg5, ops_arg arg6) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 1;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 1;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 7;
  desc->args = (ops_arg *)malloc(7 * sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg6.dat->index;
  desc->function = ops_par_loop_generate_chunk_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(1, "generate_chunk_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif

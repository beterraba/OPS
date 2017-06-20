//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"
#include "./OpenMP4/update_halo_kernel2_xvel_plus_4_back_openmp4_kernel_c.c"

#define OPS_GPU

int xdim0_update_halo_kernel2_xvel_plus_4_back;
int xdim0_update_halo_kernel2_xvel_plus_4_back_h = -1;
int ydim0_update_halo_kernel2_xvel_plus_4_back;
int ydim0_update_halo_kernel2_xvel_plus_4_back_h = -1;
int xdim1_update_halo_kernel2_xvel_plus_4_back;
int xdim1_update_halo_kernel2_xvel_plus_4_back_h = -1;
int ydim1_update_halo_kernel2_xvel_plus_4_back;
int ydim1_update_halo_kernel2_xvel_plus_4_back_h = -1;

void ops_par_loop_update_halo_kernel2_xvel_plus_4_back(char const *name,
                                                       ops_block block, int dim,
                                                       int *range, ops_arg arg0,
                                                       ops_arg arg1,
                                                       ops_arg arg2) {

  // Timing
  double t1, t2, c1, c2;
  ops_arg args[3] = {arg0, arg1, arg2};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 3, range, 66))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(66, "update_halo_kernel2_xvel_plus_4_back");
    OPS_kernels[66].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute localy allocated range for the sub-block

  int start[3];
  int end[3];
#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 3; n++) {
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
  for (int n = 0; n < 3; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);
  int z_size = MAX(0, end[2] - start[2]);

  xdim0 = args[0].dat->size[0];
  ydim0 = args[0].dat->size[1];
  xdim1 = args[1].dat->size[0];
  ydim1 = args[1].dat->size[1];
  if (xdim0 != xdim0_update_halo_kernel2_xvel_plus_4_back_h ||
      ydim0 != ydim0_update_halo_kernel2_xvel_plus_4_back_h ||
      xdim1 != xdim1_update_halo_kernel2_xvel_plus_4_back_h ||
      ydim1 != ydim1_update_halo_kernel2_xvel_plus_4_back_h) {
    xdim0_update_halo_kernel2_xvel_plus_4_back = xdim0;
    xdim0_update_halo_kernel2_xvel_plus_4_back_h = xdim0;
    ydim0_update_halo_kernel2_xvel_plus_4_back = ydim0;
    ydim0_update_halo_kernel2_xvel_plus_4_back_h = ydim0;
    xdim1_update_halo_kernel2_xvel_plus_4_back = xdim1;
    xdim1_update_halo_kernel2_xvel_plus_4_back_h = xdim1;
    ydim1_update_halo_kernel2_xvel_plus_4_back = ydim1;
    ydim1_update_halo_kernel2_xvel_plus_4_back_h = ydim1;
  }

  int *arg2h = (int *)arg2.data;
// Upload large globals
#ifdef OPS_GPU
  int consts_bytes = 0;
  consts_bytes += ROUND_UP(NUM_FIELDS * sizeof(int));
  int OPS_consts_bytes = 4 * consts_bytes;
  OPS_consts_h = (char *)malloc(OPS_consts_bytes);
  memset(OPS_consts_h, 0, OPS_consts_bytes);
  consts_bytes = 0;
  args[2].data = OPS_consts_h + consts_bytes;
  args[2].data_d = OPS_consts_d + consts_bytes;
  for (int d = 0; d < NUM_FIELDS; d++)
    ((int *)args[2].data)[d] = arg2h[d];
  consts_bytes += ROUND_UP(NUM_FIELDS * sizeof(int));
#endif // OPS_GPU

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              args[0].dat->elem_size * start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * start[1] *
              args[0].stencil->stride[1];
  base0 = base0 +
          args[0].dat->elem_size * args[0].dat->size[0] * args[0].dat->size[1] *
              start[2] * args[0].stencil->stride[2];
#ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data);
#else
  double *p_a0 = (double *)((char *)args[0].data + base0);
#endif

  int base1 = args[1].dat->base_offset +
              args[1].dat->elem_size * start[0] * args[1].stencil->stride[0];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * start[1] *
              args[1].stencil->stride[1];
  base1 = base1 +
          args[1].dat->elem_size * args[1].dat->size[0] * args[1].dat->size[1] *
              start[2] * args[1].stencil->stride[2];
#ifdef OPS_GPU
  double *p_a1 = (double *)((char *)args[1].data);
#else
  double *p_a1 = (double *)((char *)args[1].data + base1);
#endif

#ifdef OPS_GPU
  int *p_a2 = (int *)args[2].data;
#else
  int *p_a2 = arg2h;
#endif
  int tot0 = 1;
  for (int i = 0; i < args[0].dat->block->dims; i++)
    tot0 = tot0 * args[0].dat->size[i];
  int tot1 = 1;
  for (int i = 0; i < args[1].dat->block->dims; i++)
    tot1 = tot1 * args[1].dat->size[i];

#ifdef OPS_GPU
  for (int n = 0; n < 3; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 1) {
      int size = 1;
      for (int i = 0; i < args[2].dat->block->dims; i++)
        size += size * args[2].dat->size[i];
#pragma omp target update to(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_device(args, 3);
#else
  for (int n = 0; n < 3; n++)
    if (args[n].argtype == OPS_ARG_DAT && args[n].dat->dirty_hd == 2) {
      int size = 1;
      for (int i = 0; i < args[2].dat->block->dims; i++)
        size += size * args[2].dat->size[i];
#pragma omp target update from(args[n].dat->data[0 : size])
      args[n].dat->dirty_hd = 0;
    }
// ops_H_D_exchanges_host(args, 3);
#endif
  ops_halo_exchanges(args, 3, range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[66].mpi_time += t2 - t1;
  }

  update_halo_kernel2_xvel_plus_4_back_c_wrapper(
      p_a0, base0 / args[0].dat->elem_size, tot0, p_a1,
      base1 / args[1].dat->elem_size, tot1, p_a2, NUM_FIELDS, x_size, y_size,
      z_size);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[66].time += t1 - t2;
  }
#ifdef OPS_GPU
  for (int n = 0; n < 3; n++) {
    if ((args[n].argtype == OPS_ARG_DAT) &&
        (args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
         args[n].acc == OPS_RW)) {
      args[n].dat->dirty_hd = 2;
    }
  }
// ops_set_dirtybit_device(args, 3);
#else
  for (int n = 0; n < 3; n++) {
    if ((args[n].argtype == OPS_ARG_DAT) &&
        (args[n].acc == OPS_INC || args[n].acc == OPS_WRITE ||
         args[n].acc == OPS_RW)) {
      args[n].dat->dirty_hd = 1;
    }
  }
// ops_set_dirtybit_host(args, 3);
#endif
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[1], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[66].mpi_time += t2 - t1;
    OPS_kernels[66].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[66].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
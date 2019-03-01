//
// auto-generated by ops.py
//

// user function
inline void initialise_chunk_kernel_yy(int *yy, int *idx) {
  yy[OPS_ACC0(0, 0)] = idx[1] - 2;
}

// host stub function
void ops_par_loop_initialise_chunk_kernel_yy(char const *name, ops_block block,
                                             int dim, int *range, ops_arg arg0,
                                             ops_arg arg1) {

  // Timing
  double t1, t2, c1, c2;

  char *p_a[2];
  int offs[2][2];
  ops_arg args[2] = {arg0, arg1};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 2, range, 1))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(1, "initialise_chunk_kernel_yy");
    OPS_kernels[1].count++;
    ops_timers_core(&c2, &t2);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];

#ifdef OPS_MPI
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
#ifdef OPS_DEBUG
  ops_register_args(args, "initialise_chunk_kernel_yy");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension
  offs[0][1] =
      off2D(1, &start[0], &end[0], args[0].dat->size, args[0].stencil->stride) -
      offs[0][0];

  int arg_idx[2];
#ifdef OPS_MPI
  arg_idx[0] = sb->decomp_disp[0] + start[0];
  arg_idx[1] = sb->decomp_disp[1] + start[1];
#else
  arg_idx[0] = start[0];
  arg_idx[1] = start[1];
#endif

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);

  // set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset +
              (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
                  start[0] * args[0].stencil->stride[0];
  base0 = base0 +
          (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size) *
              args[0].dat->size[0] * start[1] * args[0].stencil->stride[1];
  p_a[0] = (char *)args[0].data + base0;

  p_a[1] = (char *)arg_idx;

  // initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args, 2, range);
  ops_H_D_exchanges_host(args, 2);

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[1].mpi_time += t1 - t2;
  }

  int n_x;
  for (int n_y = start[1]; n_y < end[1]; n_y++) {
#pragma novector
    for (n_x = start[0];
         n_x < start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
         n_x += SIMD_VEC) {
      // call kernel function, passing in pointers to data -vectorised
      for (int i = 0; i < SIMD_VEC; i++) {
        initialise_chunk_kernel_yy((int *)p_a[0] + i * 0 * 1, (int *)p_a[1]);

        arg_idx[0]++;
      }

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
    }

    for (int n_x = start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
         n_x < end[0]; n_x++) {
      // call kernel function, passing in pointers to data - remainder
      initialise_chunk_kernel_yy((int *)p_a[0], (int *)p_a[1]);

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0);
      arg_idx[0]++;
    }

    // shift pointers to data y direction
    p_a[0] = p_a[0] + (dat0 * off0_1);
#ifdef OPS_MPI
    arg_idx[0] = sb->decomp_disp[0] + start[0];
#else
    arg_idx[0] = start[0];
#endif
    arg_idx[1]++;
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[1].time += t2 - t1;
  }
  ops_set_dirtybit_host(args, 2);
  ops_set_halo_dirtybit3(&args[0], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c1, &t1);
    OPS_kernels[1].mpi_time += t1 - t2;
    OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg0);
  }
}

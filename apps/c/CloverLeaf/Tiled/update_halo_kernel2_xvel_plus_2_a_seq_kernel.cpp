//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_update_halo_kernel2_xvel_plus_2_a*1+x+xdim0_update_halo_kernel2_xvel_plus_2_a*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_update_halo_kernel2_xvel_plus_2_a*1+x+xdim1_update_halo_kernel2_xvel_plus_2_a*(y))


//user function

// host stub function
void ops_par_loop_update_halo_kernel2_xvel_plus_2_a_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[3] = { arg0, arg1, arg2};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,3,range,52)) return;
  #endif

  if (OPS_diags > 1) {
    OPS_kernels[52].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel2_xvel_plus_2_a");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ xvel0 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ xvel1 = (double *)(args[1].data + base1);

  const int * __restrict__ fields = (int *)args[2].data;



  //initialize global variable with the dimension of dats
  int xdim0_update_halo_kernel2_xvel_plus_2_a = args[0].dat->size[0];
  int xdim1_update_halo_kernel2_xvel_plus_2_a = args[1].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[52].mpi_time += t1-t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #ifdef intel
    #pragma loop_count(10000)
    #pragma omp simd aligned(xvel0,xvel1)
    #else
    #pragma simd
    #endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      
  if(fields[FIELD_XVEL0] == 1) xvel0[OPS_ACC0(0,0)] = xvel0[OPS_ACC0(0,2)];
  if(fields[FIELD_XVEL1] == 1) xvel1[OPS_ACC1(0,0)] = xvel1[OPS_ACC1(0,2)];

    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[52].time += t2-t1;
  }

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[52].mpi_time += t1-t2;
    OPS_kernels[52].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[52].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1


void ops_par_loop_update_halo_kernel2_xvel_plus_2_a(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 52;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 52;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 3;
  desc->args = (ops_arg*)malloc(3*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  char *tmp = (char*)malloc(NUM_FIELDS*sizeof(int));
  memcpy(tmp, arg2.data,NUM_FIELDS*sizeof(int));
  desc->args[2].data = tmp;
  desc->function = ops_par_loop_update_halo_kernel2_xvel_plus_2_a_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(52,"update_halo_kernel2_xvel_plus_2_a");
  }
  ops_enqueue_kernel(desc);
  }

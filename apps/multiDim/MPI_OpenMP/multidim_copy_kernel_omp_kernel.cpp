//
// auto-generated by ops.py
//
#define OPS_ACC_MD0(d,x,y) ((x)*2+(d)+(xdim0*(y)*2))
#define OPS_ACC_MD1(d,x,y) ((x)*2+(d)+(xdim1*(y)*2))
#ifdef _OPENMP
#include <omp.h>
#endif

//user function
inline 
void multidim_copy_kernel(const double *src, double *dest){
  dest[OPS_ACC_MD1(0,0,0)] = src[OPS_ACC_MD0(0,0,0)];
  dest[OPS_ACC_MD1(1,0,0)] = src[OPS_ACC_MD0(1,0,0)];
}



#undef OPS_ACC_MD0
#undef OPS_ACC_MD1


// host stub function
void ops_par_loop_multidim_copy_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c1,&t1);


  int  offs[2][2];
  ops_arg args[2] = { arg0, arg1};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,1)) return;
  #endif

  ops_timing_realloc(1,"multidim_copy_kernel");
  OPS_kernels[1].count++;

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
  #else //OPS_MPI
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI
  #ifdef OPS_DEBUG
  ops_register_args(args, "multidim_copy_kernel");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = args[1].dat->elem_size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];

  ops_H_D_exchanges_host(args, 2);

  //Halo Exchanges
  ops_halo_exchanges(args,2,range);


  ops_timers_core(&c2,&t2);
  OPS_kernels[1].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = end[1]-start[1];
    char *p_a[2];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start_i;

    //set up initial pointers 
    int d_m[OPS_MAX_DIM];
    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
    #endif //OPS_MPI
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
    p_a[0] = (char *)args[0].data + base0;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
    #endif //OPS_MPI
    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
    p_a[1] = (char *)args[1].data + base1;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          multidim_copy_kernel(  (const double * )p_a[0]+ i*1*2, (double * )p_a[1]+ i*1*2 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        multidim_copy_kernel(  (const double * )p_a[0], (double * )p_a[1] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0);
        p_a[1]= p_a[1] + (dat1 * off1_0);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
      p_a[1]= p_a[1] + (dat1 * off1_1);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[1].time += t1-t2;

  ops_set_dirtybit_host(args, 2);

  ops_set_halo_dirtybit3(&args[1],range);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[1].mpi_time += t2-t1;
  OPS_kernels[1].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[1].transfer += ops_compute_transfer(dim, range, &arg1);
}

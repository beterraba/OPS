//
// auto-generated by ops.py on 2014-07-31 17:05
//

//user function
#include "advec_mom_kernel.h"

// host stub function
void ops_par_loop_advec_mom_kernel1_x_nonvector(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4) {

  char *p_a[5];
  int  offs[5][3];
  ops_arg args[5] = { arg0, arg1, arg2, arg3, arg4};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = sb->istart[n];end[n] = sb->iend[n]+1;
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end[n] = sb->sizes[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel1_x_nonvector");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off3D(1, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][0];
  offs[0][2] = off3D(2, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off3D(1, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][0];
  offs[1][2] = off3D(2, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][1] - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off3D(1, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][0];
  offs[2][2] = off3D(2, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][1] - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off3D(1, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][0];
  offs[3][2] = off3D(2, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][1] - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off3D(1, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][0];
  offs[4][2] = off3D(2, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][1] - offs[4][0];



  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(19,"advec_mom_kernel1_x_nonvector");
  ops_timers_core(&c2,&t2);

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int off2_2 = offs[2][2];
  int dat2 = args[2].dat->size;
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int off3_2 = offs[3][2];
  int dat3 = args[3].dat->size;
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int off4_2 = offs[4][2];
  int dat4 = args[4].dat->size;

  //set up initial pointers and exchange halos if nessasary
  int base0 = dat0 * 1 * 
  (start[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  p_a[0] = (char *)args[0].data + base0;

  int base1 = dat1 * 1 * 
  (start[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  p_a[1] = (char *)args[1].data + base1;

  int base2 = dat2 * 1 * 
  (start[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  p_a[2] = (char *)args[2].data + base2;

  int base3 = dat3 * 1 * 
  (start[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    args[3].dat->block_size[1] *
    (start[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);
  p_a[3] = (char *)args[3].data + base3;

  int base4 = dat4 * 1 * 
  (start[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    args[4].dat->block_size[1] *
    (start[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);
  p_a[4] = (char *)args[4].data + base4;


  ops_H_D_exchanges(args,5);
  ops_halo_exchanges(args,5,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[19].mpi_time += t1-t2;

  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  ydim0 = args[0].dat->block_size[1];
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  ydim1 = args[1].dat->block_size[1];
  xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  ydim2 = args[2].dat->block_size[1];
  xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  ydim3 = args[3].dat->block_size[1];
  xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  ydim4 = args[4].dat->block_size[1];

  int n_x;
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #pragma novector
      for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          advec_mom_kernel1_x_nonvector(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (double *)p_a[2]+ i*1,
           (double *)p_a[3]+ i*1, (double *)p_a[4]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
        p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
        p_a[4]= p_a[4] + (dat4 * off4_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          advec_mom_kernel1_x_nonvector(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3], (double *)p_a[4] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0);
          p_a[1]= p_a[1] + (dat1 * off1_0);
          p_a[2]= p_a[2] + (dat2 * off2_0);
          p_a[3]= p_a[3] + (dat3 * off3_0);
          p_a[4]= p_a[4] + (dat4 * off4_0);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
      }
      //shift pointers to data z direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
    }
    ops_timers_core(&c2,&t2);
    OPS_kernels[19].time += t2-t1;
    ops_set_dirtybit_host(args, 5);
    ops_set_halo_dirtybit3(&args[2],range);

    #ifdef OPS_DEBUG
    ops_dump3(arg2.dat,"advec_mom_kernel1_x_nonvector");
    #endif

    //Update kernel record
    OPS_kernels[19].count++;
    OPS_kernels[19].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[19].transfer += ops_compute_transfer(dim, range, &arg1);
    OPS_kernels[19].transfer += ops_compute_transfer(dim, range, &arg2);
    OPS_kernels[19].transfer += ops_compute_transfer(dim, range, &arg3);
    OPS_kernels[19].transfer += ops_compute_transfer(dim, range, &arg4);
  }

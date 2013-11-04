//
// auto-generated by ops.py on 2013-11-04 17:14
//

#include "lib.h"
//user function
#include "update_halo_kernel.h"

// host stub function
void ops_par_loop_update_halo_kernel2_yvel_plus_4_b(char const *name, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  char *p_a[2];
  int  offs[2][2];
  int  count[dim];

  ops_arg args[2] = { arg0, arg1};


  for ( int i=0; i<2; i++ ){
    if (args[i].stencil!=NULL) {
      offs[i][0] = 1;  //unit step in x dimension
      offs[i][1] = ops_offs_set(range[0],range[2]+1, args[i]) - ops_offs_set(range[1],range[2], args[i]);
      //stride in y as x stride is 0
      if (args[i].stencil->stride[0] == 0) {
        offs[i][0] = 0;
        offs[i][1] = args[i].dat->block_size[0];
      }
      //stride in x as y stride is 0
      else if (args[i].stencil->stride[1] == 0) {
        offs[i][0] = 1;
        offs[i][1] = -( range[1] - range[0] );
      }
    }
  }
  int off0_1 = offs[0][0];
  int off0_2 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_1 = offs[1][0];
  int off1_2 = offs[1][1];
  int dat1 = args[1].dat->size;

  //set up initial pointers
  p_a[0] = (char *)args[0].data
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * args[0].stencil->stride[1] - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * args[0].stencil->stride[0] - args[0].dat->offset[0] );

  p_a[1] = (char *)args[1].data
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * args[1].stencil->stride[1] - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * args[1].stencil->stride[0] - args[1].dat->offset[0] );


  xdim0 = args[0].dat->block_size[0];
  xdim1 = args[1].dat->block_size[0];

  for ( int n_y=range[2]; n_y<range[3]; n_y++ ){
    for ( int n_x=range[0]; n_x<range[1]; n_x++ ){
      //call kernel function, passing in pointers to data

      update_halo_kernel2_yvel_plus_4_b(  (double *)p_a[0], (double *)p_a[1] );


      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
      p_a[1]= p_a[1] + (dat1 * off1_1);
    }

    //shift pointers to data y direction
    p_a[0]= p_a[0] + (dat0 * off0_2);
    p_a[1]= p_a[1] + (dat1 * off1_2);
  }
}

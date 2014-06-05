//
// auto-generated by ops.py on 2014-05-28 14:33
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define OPS_3D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_generate_chunk_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "generate_chunk_kernel.h"

void generate()
{

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz[] = {x_min-2,x_max+2,y_min-2,y_max+2,z_min-2,z_max+2};

  ops_par_loop_generate_chunk_kernel("generate_chunk_kernel", clover_grid, 3, rangexyz,
               ops_arg_dat(vertexx, S3D_000_P100_STRID3D_X, "double", OPS_READ),
               ops_arg_dat(vertexy, S3D_000_0P10_STRID3D_Y, "double", OPS_READ),
               ops_arg_dat(vertexz, S3D_000_00P1_STRID3D_Z, "double", OPS_READ),
               ops_arg_dat(energy0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(density0, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(xvel0, S3D_000_fP1P1P1, "double", OPS_WRITE),
               ops_arg_dat(yvel0, S3D_000_fP1P1P1, "double", OPS_WRITE),
               ops_arg_dat(zvel0, S3D_000_fP1P1P1, "double", OPS_WRITE),
               ops_arg_dat(cellx, S3D_000_STRID3D_X, "double", OPS_READ),
               ops_arg_dat(celly, S3D_000_STRID3D_Y, "double", OPS_READ),
               ops_arg_dat(cellz, S3D_000_STRID3D_Z, "double", OPS_READ));
}
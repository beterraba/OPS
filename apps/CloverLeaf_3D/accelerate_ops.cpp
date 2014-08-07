//
// auto-generated by ops.py on 2014-08-04 14:23
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

void ops_par_loop_accelerate_kernel(char const *, ops_block, int , int*,
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
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "accelerate_kernel.h"

void accelerate()
{
  error_condition = 0;

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz_inner_plus1[] = {x_min,x_max+1,y_min,y_max+1,z_min,z_max+1,};

  ops_par_loop_accelerate_kernel("accelerate_kernel", clover_grid, 3, rangexyz_inner_plus1,
               ops_arg_dat(density0, S3D_000_fM1M1M1, "double", OPS_READ),
               ops_arg_dat(volume, S3D_000_fM1M1M1, "double", OPS_READ),
               ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(xvel0, S3D_000, "double", OPS_READ),
               ops_arg_dat(xvel1, S3D_000, "double", OPS_INC),
               ops_arg_dat(xarea, S3D_000_f0M1M1, "double", OPS_READ),
               ops_arg_dat(pressure, S3D_000_fM1M1M1, "double", OPS_READ),
               ops_arg_dat(yvel0, S3D_000, "double", OPS_READ),
               ops_arg_dat(yvel1, S3D_000, "double", OPS_INC),
               ops_arg_dat(yarea, S3D_000_fM10M1, "double", OPS_READ),
               ops_arg_dat(viscosity, S3D_000_fM1M1M1, "double", OPS_READ),
               ops_arg_dat(zvel0, S3D_000, "double", OPS_READ),
               ops_arg_dat(zvel1, S3D_000, "double", OPS_INC),
               ops_arg_dat(zarea, S3D_000_fM1M10, "double", OPS_READ));
}

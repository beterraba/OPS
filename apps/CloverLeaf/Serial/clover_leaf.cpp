/* Crown Copyright 2012 AWE.

  This file is part of CloverLeaf.

  CloverLeaf is free software: you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  CloverLeaf is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  CloverLeaf. If not, see http://www.gnu.org/licenses/. */

/** @brief CloverLeaf top level program: Invokes the main cycle
  * @author Wayne Gaudin, converted to OPS by Gihan Mudalige
  * @details CloverLeaf in a proxy-app that solves the compressible Euler
  *  Equations using an explicit finite volume method on a Cartesian grid.
  *  The grid is staggered with internal energy, density and pressure at cell
  *  centres and velocities on cell vertices.

  *  A second order predictor-corrector method is used to advance the solution
  *  in time during the Lagrangian phase. A second order advective remap is then
  *  carried out to return the mesh to an orthogonal state.
  *
  *  NOTE: that the proxy-app uses uniformly spaced mesh. The actual method will
  *  work on a mesh with varying spacing to keep it relevant to it's parent code.
  *  For this reason, optimisations should only be carried out on the software
  *  that do not change the underlying numerical method. For example, the
  *  volume, though constant for all cells, should remain array and not be
  *  converted to a scalar.
  *
  *  This version is based on C/C++ and uses the OPS prototype highlevel domain
  *  specific API for developing Structured mesh applications
  */

// standard headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// OPS header file
#include "ops_seq.h"

// Cloverleaf constants
#include "data.h"

// Cloverleaf definitions
#include "definitions.h"

//Cloverleaf kernels



// Cloverleaf functions
void initialise();
void generate();
void ideal_gas(int predict);
void update_halo(int* fields, int depth);
void field_summary();
void timestep();
void PdV(int predict);
void accelerate();
void flux_calc();
void advection(int);
void reset_field();



/******************************************************************************
* Initialize Global constants and variables
/******************************************************************************/


/**----------Cloverleaf Vars/Consts--------------**/

float   g_version = 1.0;
int     g_ibig = 640000;
double  g_small = 1.0e-16;
double  g_big  = 1.0e+21;
int     g_name_len_max = 255 ,
        g_xdir = 1,
        g_ydir = 2;

int     number_of_states;

        //These two need to be kept consistent with update_halo
int     CHUNK_LEFT    = 1,
        CHUNK_RIGHT   = 2,
        CHUNK_BOTTOM  = 3,
        CHUNK_TOP     = 4,
        EXTERNAL_FACE = -1;

int     FIELD_DENSITY0   = 0,
        FIELD_DENSITY1   = 1,
        FIELD_ENERGY0    = 2,
        FIELD_ENERGY1    = 3,
        FIELD_PRESSURE   = 4,
        FIELD_VISCOSITY  = 5,
        FIELD_SOUNDSPEED = 6,
        FIELD_XVEL0      = 7,
        FIELD_XVEL1      = 8,
        FIELD_YVEL0      = 9,
        FIELD_YVEL1      =10,
        FIELD_VOL_FLUX_X =11,
        FIELD_VOL_FLUX_Y =12,
        FIELD_MASS_FLUX_X=13,
        FIELD_MASS_FLUX_Y=14,
        NUM_FIELDS       =15;

FILE    *g_out, *g_in;  //Files for input and output

int     g_rect=1,
        g_circ=2,
        g_point=3;

state_type * states; //global variable holding state info

grid_type grid; //global variable holding global grid info

field_type field; //global variable holding info of fields

int step ;
int advect_x; //logical
int error_condition;
int test_problem;
int state_max;
int complete; //logical

int fields[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double dtold, dt, time, dtinit, dtmin, dtmax, dtrise, dtu_safe, dtv_safe, dtc_safe,
       dtdiv_safe, dtc, dtu, dtv, dtdiv;

double end_time;
int end_step;
int visit_frequency;
int summary_frequency;


int jdt, kdt;

#include "cloverleaf_ops_vars.h"


/******************************************************************************
* Main program
/******************************************************************************/
int main(int argc, char **argv)
{

  /**--------------------Set up Cloverleaf default problem-------------------**/

  //some defailt values before read input

  test_problem = 0;
  state_max = 0;

  grid = (grid_type ) xmalloc(sizeof(grid_type_core));
  grid->xmin = 0;
  grid->ymin = 0;
  grid->xmax = 100;
  grid->ymax = 100;

  grid->x_cells = 10;
  grid->y_cells = 10;

  end_time = 10.0;
  end_step = g_ibig;
  complete = FALSE;


  visit_frequency=10;
  summary_frequency=10;

  dtinit = 0.1;
  dtmax = 1.0;
  dtmin = 0.0000001;
  dtrise = 1.5;
  dtc_safe = 0.7;
  dtu_safe = 0.5;
  dtv_safe = 0.5;
  dtdiv_safe = 0.7;

  //
  //need to read in the following through I/O
  //

  grid->x_cells = 10;
  grid->y_cells = 2;

  grid->xmin = 0;
  grid->ymin = 0;
  grid->xmax = grid->x_cells;
  grid->ymax = grid->y_cells;

  field = (field_type ) xmalloc(sizeof(field_type_core));
  field->x_min = 0;
  field->y_min = 0;
  field->x_max = grid->x_cells;
  field->y_max = grid->y_cells;
  field->left = 0;
  field->bottom = 0;

  number_of_states = 2;
  states =  (state_type *) xmalloc(sizeof(state_type) * number_of_states);

  //state 1
  states[0] = (state_type ) xmalloc(sizeof(state_type_core));
  states[0]->density = 0.2;
  states[0]->energy = 1.0;
  states[0]->xvel = 0.0;
  states[0]->yvel = 0.0;

  //state 2
  states[1] = (state_type ) xmalloc(sizeof(state_type_core));
  states[1]->density=1.0;
  states[1]->energy=2.5;
  states[1]->xvel = 0.0;
  states[1]->yvel = 0.0;
  states[1]->geometry=g_rect;
  states[1]->xmin=0.0;
  states[1]->xmax=5.0;
  states[1]->ymin=0.0;
  states[1]->ymax=2.0;

  float dx= (grid->xmax-grid->xmin)/(float)(grid->x_cells);
  float dy= (grid->ymax-grid->ymin)/(float)(grid->y_cells);

  for(int i = 0; i < number_of_states; i++)
  {
    states[i]->xmin = states[i]->xmin + (dx/100.00);
    states[i]->ymin = states[i]->ymin + (dy/100.00);
    states[i]->xmax = states[i]->xmax - (dx/100.00);
    states[i]->ymax = states[i]->ymax - (dy/100.00);
  }

  NUM_FIELDS = 15;

  dtinit = 0.04; //initial_timestep
  dtmax = 0.04; //max_timestep
  dtmin = 0.0000001;
  dtrise = 1.5; //timestep_rise
  end_time = 3.0; // end_time
  //end_step = 0.5; //end_step

  summary_frequency = 10;
  test_problem = 1;

  //
  //end of I/O
  //

  /**-------------------OPS Initialisation and Declarations------------------**/

  // OPS initialisation
  ops_init(argc,argv,5);
  ops_printf("Clover version %f\n", g_version);

  //
  //declare blocks
  //
  int x_cells = grid->x_cells;
  int y_cells = grid->y_cells;
  int x_min = field->x_min;
  int x_max = field->x_max;
  int y_min = field->y_min;
  int y_max = field->y_max;
  int dims[2] = {x_cells, y_cells};  //cloverleaf 2D block dimensions
  ops_block clover_grid = ops_decl_block(2, dims, "grid");

  //declare edges of block
  dims[0] = x_cells; dims[1] = 1;
  clover_xedge = ops_decl_block(2, dims, "xedge");

  dims[0] = 1; dims[1] = y_cells;
  clover_yedge = ops_decl_block(2, dims, "yedge");

  //
  //declare data on blocks
  //
  int offset[2] = {-2,-2};
  int size[2] = {(x_max+2)-(x_min-2), (y_max+2)-(y_min-2)};
  double* temp = NULL;

  density0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "density0");
  density1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "density1");
  energy0     = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "energy0");
  energy1     = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "energy1");
  pressure    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "pressure");
  viscosity   = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "viscosity");
  soundspeed  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "soundspeed");
  volume      = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "volume");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  xvel0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xvel0");
  xvel1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xvel1");
  yvel0    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yvel0");
  yvel1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yvel1");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+2)-(y_min-2);
  vol_flux_x  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "vol_flux_x");
  mass_flux_x = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "mass_flux_x");
  xarea       = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "xarea");

  size[0] = (x_max+2)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  vol_flux_y  = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "vol_flux_y");
  mass_flux_y = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "mass_flux_y");
  yarea       = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "yarea");

  size[0] = (x_max+3)-(x_min-2); size[1] = (y_max+3)-(y_min-2);
  work_array1    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array1");
  work_array2    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array2");
  work_array3    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array3");
  work_array4    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array4");
  work_array5    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array5");
  work_array6    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array6");
  work_array7    = ops_decl_dat(clover_grid, 1, size, offset, temp, "double", "work_array7");

  int size2[2] = {(x_max+2)-(x_min-2),1};
  int size3[2] = {1, (y_max+2)-(y_min-2)};
  int size4[2] = {(x_max+3)-(x_min-2),1};
  int size5[2] = {1,(y_max+3)-(y_min-2)};
  int offsetx[2] = {-2,0};
  int offsety[2] = {0,-2};
  cellx    = ops_decl_dat(clover_xedge, 1, size2, offsetx, temp, "double", "cellx");
  celly    = ops_decl_dat(clover_yedge, 1, size3, offsety, temp, "double", "celly");
  vertexx  = ops_decl_dat(clover_xedge, 1, size4, offsetx, temp, "double", "vertexx");
  vertexy  = ops_decl_dat(clover_yedge, 1, size5, offsety, temp, "double", "vertexy");
  celldx   = ops_decl_dat(clover_xedge, 1, size2, offsetx, temp, "double", "celldx");
  celldy   = ops_decl_dat(clover_yedge, 1, size3, offsety, temp, "double", "celldy");
  vertexdx = ops_decl_dat(clover_xedge, 1, size4, offsetx, temp, "double", "vertexdx");
  vertexdy = ops_decl_dat(clover_yedge, 1, size5, offsety, temp, "double", "vertexdy");

  //contains x indicies from 0 to xmax+3 -- needed for initialization
  int* xindex = (int *)xmalloc(sizeof(int)*size4[0]);
  for(int i=x_min-2; i<x_max+3; i++) xindex[i-offsetx[0]] = i - x_min;
  xx  = ops_decl_dat(clover_xedge, 1, size4, offsetx, xindex, "int", "xx");

  //contains y indicies from 0 to ymax+3 -- needed for initialization
  int* yindex = (int *)xmalloc(sizeof(int)*size5[1]);
  for(int i=y_min-2; i<y_max+3; i++) yindex[i-offsety[1]] = i - y_min;
  yy  = ops_decl_dat(clover_yedge, 1, size5, offsety, yindex, "int", "yy");


  //
  //Declare commonly used stencils
  //
  int s2D[]            = {0,0};
  int s2D_00_P10[]     = {0,0, 1,0};
  int s2D_00_0P1[]     = {0,0, 0,1};
  int s2D_00_M10[]     = {0,0, -1,0};
  int s2D_00_0M1[]     = {0,0, 0,-1};
  int s2D_00_P10_M10[] = {0,0, 1,0, -1,0};
  int s2D_00_0P1_0M1[] = {0,0, 0,1, 0,-1};
  int s2D_00_M10_M20[] = {0,0, -1,0, -2,0};
  int s2D_00_0M1_0M2[] = {0,0, 0,-1, 0,-2};
  int s2D_00_P20[]     = {0,0, 2,0};
  int s2D_00_0P2[]     = {0,0, 0,2};
  int s2D_00_M20[]     = {0,0, -2,0};
  int s2D_00_0M2[]     = {0,0, 0,-2};

  S2D_00         = ops_decl_stencil( 2, 1, s2D, "00");

  S2D_00_P10     = ops_decl_stencil( 2, 2, s2D_00_P10, "0,0:1,0");
  S2D_00_0P1     = ops_decl_stencil( 2, 2, s2D_00_0P1, "0,0:0,1");
  S2D_00_M10     = ops_decl_stencil( 2, 2, s2D_00_M10, "0,0:-1,0");
  S2D_00_0M1     = ops_decl_stencil( 2, 2, s2D_00_0M1, "0,0:0,-1");

  S2D_00_P10_M10 = ops_decl_stencil( 2, 3, s2D_00_P10_M10, "0,0:1,0:1,0");
  S2D_00_0P1_0M1 = ops_decl_stencil( 2, 3, s2D_00_0P1_0M1, "0,0:0,1:0,-1");

  S2D_00_M10_M20 = ops_decl_stencil( 2, 3, s2D_00_M10_M20, "0,0:-1,0:-2,0");
  S2D_00_0M1_0M2 = ops_decl_stencil( 2, 3, s2D_00_0M1_0M2, "0,0:0,-1:0,-2");

  S2D_00_P20     = ops_decl_stencil( 2, 2, s2D_00_P20, "0,0:2,0");
  S2D_00_0P2     = ops_decl_stencil( 2, 2, s2D_00_0P2, "0,0:0,2");

  S2D_00_M20     = ops_decl_stencil( 2, 2, s2D_00_M20, "0,0:-2,0");
  S2D_00_0M2     = ops_decl_stencil( 2, 2, s2D_00_0M2, "0,0:0,-2");

  int self2D_plus3x[] = {0,0, 3,0};
  sten_self2D_plus3x = ops_decl_stencil( 2, 2, self2D_plus3x, "self2D_plus3x");

  int self2D_plus3y[] = {0,0, 0,3};
  sten_self2D_plus3y = ops_decl_stencil( 2, 2, self2D_plus3y, "self2D_plus3y");

  int self2D_minus3x[] = {0,0, -3,0};
  sten_self2D_minus3x = ops_decl_stencil( 2, 2, self2D_minus3x, "self2D_minus3x");

  int self2D_minus3y[] = {0,0, 0,-3};
  sten_self2D_minus3y = ops_decl_stencil( 2, 2, self2D_minus3y, "self2D_minus3y");


  int self2D_plus4x[] = {0,0, 4,0};
  int self2D_plus4y[] = {0,0, 0,4};
  int self2D_minus4x[] = {0,0, -4,0};
  int self2D_minus4y[] = {0,0, 0,-4};

  sten_self2D_plus4x = ops_decl_stencil( 2, 2, self2D_plus4x, "self2D_plus4x");
  sten_self2D_plus4y = ops_decl_stencil( 2, 2, self2D_plus4y, "self2D_plus4y");
  sten_self2D_minus4x = ops_decl_stencil( 2, 2, self2D_minus4x, "self2D_minus4x");
  sten_self2D_minus4y = ops_decl_stencil( 2, 2, self2D_minus4y, "self2D_minus4y");


  int self2D_plus1xy[]  = {0,0, 1,0, 0,1, 1,1};
  int self2D_minus1xy[]  = {0,0, -1,0, 0,-1, -1,-1};
  sten_self2D_plus1xy = ops_decl_stencil( 2, 4, self2D_plus1xy, "self2D_plus1xy");
  sten_self2D_minus1xy = ops_decl_stencil( 2, 4, self2D_minus1xy, "self2D_minus1xy");

  int self2D_plus1x_minus1y[] = {0,0, 1,0, 0,-1, 1,-1};
  int self2D_plus1y_minus1x[] = {0,0, 0,1, -1,0, -1,1};
  sten_self2D_plus1x_minus1y= ops_decl_stencil( 2, 4, self2D_plus1x_minus1y, "self2D_plus1x_minus1y");
  sten_self2D_plus1y_minus1x= ops_decl_stencil( 2, 4, self2D_plus1y_minus1x, "self2D_plus1y_minus1x");


  int self2D_4point1xy[]  = {1,0, -1,0, 0,1, 0,-1};
  sten_self2D_4point1xy = ops_decl_stencil( 2, 4, self2D_4point1xy, "self2D_4point1xy");


  int self2D_plus_1_minus1_2_x[] = {0,0, 1,0, -1,0, -2,0};
  int self2D_plus_1_minus1_2_y[] = {0,0, 0,1, 0,-1, 0,-2};

  int self2D_plus_1_2_minus1_x[] = {0,0, 1,0, 2,0, -1,0};
  int self2D_plus_1_2_minus1_y[] = {0,0, 0,1, 0,2, 0,-1};

  int stride2D_x[] = {1,0};
  int stride2D_y[] = {0,1};
  int stride2D_null[] = {0,0};

  int xmax2D[] = {x_max+2,0};
  int ymax2D[] = {0,y_max+2};


  sten_self_stride2D_x = ops_decl_strided_stencil( 2, 1, s2D, stride2D_x, "self_stride2D_x");
  sten_self_stride2D_y = ops_decl_strided_stencil( 2, 1, s2D, stride2D_y, "self_stride2D_y");

  sten_self_plus1_stride2D_x = ops_decl_strided_stencil( 2, 2, s2D_00_P10, stride2D_x, "self_stride2D_x");
  sten_self_plus1_stride2D_y = ops_decl_strided_stencil( 2, 2, s2D_00_0P1, stride2D_y, "self_stride2D_y");

  sten_self_minus1_stride2D_x = ops_decl_strided_stencil( 2, 2, s2D_00_M10, stride2D_x, "self_stride2D_x");
  sten_self_minus1_stride2D_y = ops_decl_strided_stencil( 2, 2, s2D_00_0M1, stride2D_y, "self_stride2D_y");

  sten_self2D_plus_1_minus1_2_x = ops_decl_stencil( 2, 4, self2D_plus_1_minus1_2_x, "self2D_plus_1_minus1_2_x");
  sten_self_plus_1_minus1_2_x_stride2D_x = ops_decl_strided_stencil( 2, 4, self2D_plus_1_minus1_2_x, stride2D_x, "self_stride2D_x");
  sten_self2D_plus_1_minus1_2_y = ops_decl_stencil( 2, 4, self2D_plus_1_minus1_2_y, "self2D_plus_1_minus1_2_y");
  sten_self_plus_1_minus1_2_y_stride2D_y = ops_decl_strided_stencil( 2, 4, self2D_plus_1_minus1_2_y, stride2D_y, "self_stride2D_y");


  sten_self2D_plus_1_2_minus1x = ops_decl_stencil( 2, 4, self2D_plus_1_2_minus1_x, "self2D_plus_1_2_minus1_x");
  sten_self2D_plus_1_2_minus1y = ops_decl_stencil( 2, 4, self2D_plus_1_2_minus1_y, "self2D_plus_1_2_minus1_y");


  sten_self_stride2D_xmax = ops_decl_strided_stencil( 2, 1, xmax2D, stride2D_y, "self_stride2D_xmax");
  sten_self_nullstride2D_xmax = ops_decl_strided_stencil( 2, 1, xmax2D, stride2D_null, "self_nullstride2D_xmax");
  sten_self_stride2D_ymax = ops_decl_strided_stencil( 2, 1, ymax2D, stride2D_x, "self_stride2D_ymax");
  sten_self_nullstride2D_ymax = ops_decl_strided_stencil( 2, 1, ymax2D, stride2D_null, "self_nullstride2D_ymax");

  //print ops blocks and dats details
  ops_diagnostic_output();


  /**---------------------initialize and generate chunk----------------------**/

  initialise();

  time  = 0.0;
  step  = 0;
  dtold = dtinit;
  dt    = dtinit;

  generate();

  advect_x = TRUE;

  /**------------------------------ideal_gas---------------------------------**/


  ideal_gas(FALSE);


  /**-----------------------------update_halo--------------------------------**/

  //Prime all halo data for the first step
  fields[FIELD_DENSITY0]  = 1;
  fields[FIELD_ENERGY0]   = 1;
  fields[FIELD_PRESSURE]  = 1;
  fields[FIELD_VISCOSITY] = 1;
  fields[FIELD_DENSITY1]  = 1;
  fields[FIELD_ENERGY1]   = 1;
  fields[FIELD_XVEL0]     = 1;
  fields[FIELD_YVEL0]     = 1;
  fields[FIELD_XVEL1]     = 1;
  fields[FIELD_YVEL1]     = 1;

  update_halo(fields, 2);

  ops_fprintf(g_out,"\n");
  ops_fprintf(g_out," Problem initialised and generated\n");
  ops_fprintf(g_out,"\n");

  /**----------------------------field_summary-------------------------------**/

  field_summary();

  ops_fprintf(g_out," Starting the calculation\n");
  fclose(g_in);


  /***************************************************************************
  **-----------------------------hydro loop---------------------------------**
  /**************************************************************************/

  while(1) {

    step = step + 1;

    timestep();

    PdV(TRUE);

    accelerate();

    PdV(FALSE);

    flux_calc();

    advection(step);

    reset_field();

    if (advect_x == TRUE) advect_x = FALSE;
    else advect_x = TRUE;

    time = time + dt;

    if(summary_frequency != 0)
      if((step%summary_frequency) == 0)
        field_summary();

    if((time+g_small) > end_time || (step >= end_step)) {
      complete=TRUE;
      field_summary();
      break;
    }
  }


  fclose(g_out);
  ops_exit();
}
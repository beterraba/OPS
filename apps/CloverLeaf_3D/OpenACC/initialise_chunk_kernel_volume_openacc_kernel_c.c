//
// auto-generated by ops.py on 2014-07-31 17:05
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_initialise_chunk_kernel_volume;
int ydim0_initialise_chunk_kernel_volume;
int xdim1_initialise_chunk_kernel_volume;
int ydim1_initialise_chunk_kernel_volume;
int xdim2_initialise_chunk_kernel_volume;
int ydim2_initialise_chunk_kernel_volume;
int xdim3_initialise_chunk_kernel_volume;
int ydim3_initialise_chunk_kernel_volume;
int xdim4_initialise_chunk_kernel_volume;
int ydim4_initialise_chunk_kernel_volume;
int xdim5_initialise_chunk_kernel_volume;
int ydim5_initialise_chunk_kernel_volume;
int xdim6_initialise_chunk_kernel_volume;
int ydim6_initialise_chunk_kernel_volume;

#define OPS_ACC0(x,y,z) (x+xdim0_initialise_chunk_kernel_volume*(y)+xdim0_initialise_chunk_kernel_volume*ydim0_initialise_chunk_kernel_volume*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_initialise_chunk_kernel_volume*(y)+xdim1_initialise_chunk_kernel_volume*ydim1_initialise_chunk_kernel_volume*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_initialise_chunk_kernel_volume*(y)+xdim2_initialise_chunk_kernel_volume*ydim2_initialise_chunk_kernel_volume*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_initialise_chunk_kernel_volume*(y)+xdim3_initialise_chunk_kernel_volume*ydim3_initialise_chunk_kernel_volume*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_initialise_chunk_kernel_volume*(y)+xdim4_initialise_chunk_kernel_volume*ydim4_initialise_chunk_kernel_volume*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_initialise_chunk_kernel_volume*(y)+xdim5_initialise_chunk_kernel_volume*ydim5_initialise_chunk_kernel_volume*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_initialise_chunk_kernel_volume*(y)+xdim6_initialise_chunk_kernel_volume*ydim6_initialise_chunk_kernel_volume*(z))

//user function
inline 
void initialise_chunk_kernel_volume(double *volume, const double *celldy, double *xarea,
                                         const double *celldx, double *yarea, const double *celldz, double *zarea) {

  double d_x, d_y, d_z;

  d_x = (grid.xmax - grid.xmin)/(double)grid.x_cells;
  d_y = (grid.ymax - grid.ymin)/(double)grid.y_cells;
  d_z = (grid.zmax - grid.zmin)/(double)grid.z_cells;

  volume[OPS_ACC0(0,0,0)] = d_x*d_y*d_z;
  xarea[OPS_ACC2(0,0,0)] = celldy[OPS_ACC1(0,0,0)]*celldz[OPS_ACC5(0,0,0)];
  yarea[OPS_ACC4(0,0,0)] = celldx[OPS_ACC3(0,0,0)]*celldz[OPS_ACC5(0,0,0)];
  zarea[OPS_ACC6(0,0,0)] = celldx[OPS_ACC3(0,0,0)]*celldy[OPS_ACC1(0,0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6


void initialise_chunk_kernel_volume_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        initialise_chunk_kernel_volume(  p_a0 + n_x*1 + n_y*xdim0_initialise_chunk_kernel_volume*1 + n_z*xdim0_initialise_chunk_kernel_volume*ydim0_initialise_chunk_kernel_volume*1,
           p_a1 + n_x*0 + n_y*xdim1_initialise_chunk_kernel_volume*1 + n_z*xdim1_initialise_chunk_kernel_volume*ydim1_initialise_chunk_kernel_volume*0,
           p_a2 + n_x*1 + n_y*xdim2_initialise_chunk_kernel_volume*1 + n_z*xdim2_initialise_chunk_kernel_volume*ydim2_initialise_chunk_kernel_volume*1,
           p_a3 + n_x*1 + n_y*xdim3_initialise_chunk_kernel_volume*0 + n_z*xdim3_initialise_chunk_kernel_volume*ydim3_initialise_chunk_kernel_volume*0,
           p_a4 + n_x*1 + n_y*xdim4_initialise_chunk_kernel_volume*1 + n_z*xdim4_initialise_chunk_kernel_volume*ydim4_initialise_chunk_kernel_volume*1,
           p_a5 + n_x*0 + n_y*xdim5_initialise_chunk_kernel_volume*0 + n_z*xdim5_initialise_chunk_kernel_volume*ydim5_initialise_chunk_kernel_volume*1,
           p_a6 + n_x*1 + n_y*xdim6_initialise_chunk_kernel_volume*1 + n_z*xdim6_initialise_chunk_kernel_volume*ydim6_initialise_chunk_kernel_volume*1 );

      }
    }
  }
}

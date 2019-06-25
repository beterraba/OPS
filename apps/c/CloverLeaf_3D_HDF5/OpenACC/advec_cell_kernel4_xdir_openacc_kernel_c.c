//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_advec_cell_kernel4_xdir;
int ydim0_advec_cell_kernel4_xdir;
int xdim1_advec_cell_kernel4_xdir;
int ydim1_advec_cell_kernel4_xdir;
int xdim2_advec_cell_kernel4_xdir;
int ydim2_advec_cell_kernel4_xdir;
int xdim3_advec_cell_kernel4_xdir;
int ydim3_advec_cell_kernel4_xdir;
int xdim4_advec_cell_kernel4_xdir;
int ydim4_advec_cell_kernel4_xdir;
int xdim5_advec_cell_kernel4_xdir;
int ydim5_advec_cell_kernel4_xdir;
int xdim6_advec_cell_kernel4_xdir;
int ydim6_advec_cell_kernel4_xdir;
int xdim7_advec_cell_kernel4_xdir;
int ydim7_advec_cell_kernel4_xdir;
int xdim8_advec_cell_kernel4_xdir;
int ydim8_advec_cell_kernel4_xdir;
int xdim9_advec_cell_kernel4_xdir;
int ydim9_advec_cell_kernel4_xdir;
int xdim10_advec_cell_kernel4_xdir;
int ydim10_advec_cell_kernel4_xdir;

//user function

inline void advec_cell_kernel4_xdir(
    ptr_double density1, ptr_double energy1, const ptr_double mass_flux_x,
    const ptr_double vol_flux_x, const ptr_double pre_vol,
    const ptr_double post_vol, ptr_double pre_mass, ptr_double post_mass,
    ptr_double advec_vol, ptr_double post_ener, const ptr_double ener_flux) {

  OPS_ACC(pre_mass, 0, 0, 0) =
      OPS_ACC(density1, 0, 0, 0) * OPS_ACC(pre_vol, 0, 0, 0);
  OPS_ACC(post_mass, 0, 0, 0) = OPS_ACC(pre_mass, 0, 0, 0) +
                                OPS_ACC(mass_flux_x, 0, 0, 0) -
                                OPS_ACC(mass_flux_x, 1, 0, 0);
  OPS_ACC(post_ener, 0, 0, 0) =
      (OPS_ACC(energy1, 0, 0, 0) * OPS_ACC(pre_mass, 0, 0, 0) +
       OPS_ACC(ener_flux, 0, 0, 0) - OPS_ACC(ener_flux, 1, 0, 0)) /
      OPS_ACC(post_mass, 0, 0, 0);
  OPS_ACC(advec_vol, 0, 0, 0) = OPS_ACC(pre_vol, 0, 0, 0) +
                                OPS_ACC(vol_flux_x, 0, 0, 0) -
                                OPS_ACC(vol_flux_x, 1, 0, 0);
  OPS_ACC(density1, 0, 0, 0) =
      OPS_ACC(post_mass, 0, 0, 0) / OPS_ACC(advec_vol, 0, 0, 0);
  OPS_ACC(energy1, 0, 0, 0) = OPS_ACC(post_ener, 0, 0, 0);
}


void advec_cell_kernel4_xdir_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  double *p_a7,
  double *p_a8,
  double *p_a9,
  double *p_a10,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5,p_a6,p_a7,p_a8,p_a9,p_a10)
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
        ptr_double ptr0 = {
            p_a0 + n_x * 1 * 1 + n_y * xdim0_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim0_advec_cell_kernel4_xdir *
                    ydim0_advec_cell_kernel4_xdir * 1 * 1,
            xdim0_advec_cell_kernel4_xdir, ydim0_advec_cell_kernel4_xdir};
        ptr_double ptr1 = {
            p_a1 + n_x * 1 * 1 + n_y * xdim1_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim1_advec_cell_kernel4_xdir *
                    ydim1_advec_cell_kernel4_xdir * 1 * 1,
            xdim1_advec_cell_kernel4_xdir, ydim1_advec_cell_kernel4_xdir};
        const ptr_double ptr2 = {
            p_a2 + n_x * 1 * 1 + n_y * xdim2_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim2_advec_cell_kernel4_xdir *
                    ydim2_advec_cell_kernel4_xdir * 1 * 1,
            xdim2_advec_cell_kernel4_xdir, ydim2_advec_cell_kernel4_xdir};
        const ptr_double ptr3 = {
            p_a3 + n_x * 1 * 1 + n_y * xdim3_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim3_advec_cell_kernel4_xdir *
                    ydim3_advec_cell_kernel4_xdir * 1 * 1,
            xdim3_advec_cell_kernel4_xdir, ydim3_advec_cell_kernel4_xdir};
        const ptr_double ptr4 = {
            p_a4 + n_x * 1 * 1 + n_y * xdim4_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim4_advec_cell_kernel4_xdir *
                    ydim4_advec_cell_kernel4_xdir * 1 * 1,
            xdim4_advec_cell_kernel4_xdir, ydim4_advec_cell_kernel4_xdir};
        const ptr_double ptr5 = {
            p_a5 + n_x * 1 * 1 + n_y * xdim5_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim5_advec_cell_kernel4_xdir *
                    ydim5_advec_cell_kernel4_xdir * 1 * 1,
            xdim5_advec_cell_kernel4_xdir, ydim5_advec_cell_kernel4_xdir};
        ptr_double ptr6 = {
            p_a6 + n_x * 1 * 1 + n_y * xdim6_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim6_advec_cell_kernel4_xdir *
                    ydim6_advec_cell_kernel4_xdir * 1 * 1,
            xdim6_advec_cell_kernel4_xdir, ydim6_advec_cell_kernel4_xdir};
        ptr_double ptr7 = {
            p_a7 + n_x * 1 * 1 + n_y * xdim7_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim7_advec_cell_kernel4_xdir *
                    ydim7_advec_cell_kernel4_xdir * 1 * 1,
            xdim7_advec_cell_kernel4_xdir, ydim7_advec_cell_kernel4_xdir};
        ptr_double ptr8 = {
            p_a8 + n_x * 1 * 1 + n_y * xdim8_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim8_advec_cell_kernel4_xdir *
                    ydim8_advec_cell_kernel4_xdir * 1 * 1,
            xdim8_advec_cell_kernel4_xdir, ydim8_advec_cell_kernel4_xdir};
        ptr_double ptr9 = {
            p_a9 + n_x * 1 * 1 + n_y * xdim9_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim9_advec_cell_kernel4_xdir *
                    ydim9_advec_cell_kernel4_xdir * 1 * 1,
            xdim9_advec_cell_kernel4_xdir, ydim9_advec_cell_kernel4_xdir};
        const ptr_double ptr10 = {
            p_a10 + n_x * 1 * 1 + n_y * xdim10_advec_cell_kernel4_xdir * 1 * 1 +
                n_z * xdim10_advec_cell_kernel4_xdir *
                    ydim10_advec_cell_kernel4_xdir * 1 * 1,
            xdim10_advec_cell_kernel4_xdir, ydim10_advec_cell_kernel4_xdir};
        advec_cell_kernel4_xdir(ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7,
                                ptr8, ptr9, ptr10);
      }
    }
  }
}

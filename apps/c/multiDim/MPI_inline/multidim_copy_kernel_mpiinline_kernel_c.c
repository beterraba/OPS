//
// auto-generated by ops.py
//

int xdim0_multidim_copy_kernel;
int ydim0_multidim_copy_kernel;
int xdim1_multidim_copy_kernel;
int ydim1_multidim_copy_kernel;


//user function



void multidim_copy_kernel_c_wrapper(
  double * restrict src_p,
  double * restrict dest_p,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      #ifdef OPS_SOA
      const ptrm_double src = { src_p + n_x*1 + n_y * xdim0_multidim_copy_kernel*1, xdim0_multidim_copy_kernel, ydim0_multidim_copy_kernel};
      #else
      const ptrm_double src = { src_p + n_x*1 + n_y * xdim0_multidim_copy_kernel*1, xdim0_multidim_copy_kernel, 2};
      #endif
      #ifdef OPS_SOA
      ptrm_double dest = { dest_p + n_x*1 + n_y * xdim1_multidim_copy_kernel*1, xdim1_multidim_copy_kernel, ydim1_multidim_copy_kernel};
      #else
      ptrm_double dest = { dest_p + n_x*1 + n_y * xdim1_multidim_copy_kernel*1, xdim1_multidim_copy_kernel, 2};
      #endif

      OPS_ACC(dest, 0, 0, 0) = OPS_ACC(src, 0, 0, 0);
      OPS_ACC(dest, 1, 0, 0) = OPS_ACC(src, 1, 0, 0);
    }
  }
}

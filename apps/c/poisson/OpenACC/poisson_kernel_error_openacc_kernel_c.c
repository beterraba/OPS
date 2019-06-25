//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_poisson_kernel_error;
int xdim1_poisson_kernel_error;

//user function
inline void poisson_kernel_error(const ptr_double u, const ptr_double ref,
                                 double *err) {
  *err = *err + (OPS_ACC(u, 0,0)-OPS_ACC(ref, 0,0))*(OPS_ACC(u, 0,0)-OPS_ACC(ref, 0,0));
}


void poisson_kernel_error_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size, int y_size) {
  double p_a2_0 = p_a2[0];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1) reduction(+:p_a2_0)
  #pragma acc loop reduction(+:p_a2_0)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a2_0)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_poisson_kernel_error*1*1, xdim0_poisson_kernel_error};
      const ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_poisson_kernel_error*1*1, xdim1_poisson_kernel_error};
      poisson_kernel_error( ptr0,
          ptr1, &p_a2_0 );

    }
  }
  p_a2[0] = p_a2_0;
}

//
// auto-generated by ops.py
//
//header
#define OPS_ACC_MD_MACROS
#define OPS_3D
#ifdef __cplusplus
#include "ops_lib_cpp.h"
#endif
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif
#include "ops_cuda_rt_support.h"
#include "user_types.h"

// global constants
extern double g_small;
extern double g_big;
extern double dtc_safe;
extern double dtu_safe;
extern double dtv_safe;
extern double dtw_safe;
extern double dtdiv_safe;
extern field_type field;
extern grid_type grid;
extern state_type *states;
extern int number_of_states;
extern int g_sphe;
extern int g_point;
extern int g_cube;
extern double dt;

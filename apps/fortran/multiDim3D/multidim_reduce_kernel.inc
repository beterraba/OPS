subroutine multidim_reduce_kernel(val, redu_dat1)
  IMPLICIT NONE
  REAL   (kind=8), DIMENSION(3), INTENT(IN) :: val
  REAL(kind=8), DIMENSION(2) :: redu_dat1
  redu_dat1(1) = redu_dat1(1) + val(OPS_ACC_MD1(1,0,0,0))
  redu_dat1(2) = redu_dat1(2) + val(OPS_ACC_MD1(2,0,0,0))
  redu_dat1(3) = redu_dat1(3) + val(OPS_ACC_MD1(3,0,0,0))
end subroutine

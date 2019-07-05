      subroutine daxpy(n, alpha, x, y)
      implicit none
      integer n
      double precision alpha
      double precision x(n), y(n)
Cf2py integer intent(in) :: n
Cf2py double precision intent(in) :: alpha
Cf2py double precision intent(in), depend(n) :: x(n)
Cf2py double precision intent(in,out), depend(n) :: y(n)
      integer i
      do i = 1, n
         y(i) = alpha * x(i) + y(i)
      enddo
      end subroutine

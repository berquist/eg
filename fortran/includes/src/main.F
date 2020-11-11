      program includes
      implicit none

C     Derived from https://docs.oracle.com/cd/E19957-01/805-4939/6j4m0vnaj/index.html

      character heading*(*)
      real epsilon
      logical t

      parameter (epsilon=1.0e-6, heading=" IO Error #", t
     $     =.true.)

      include "test_header.F"

      write (*,*) "epsilon: ", epsilon
      write (*,*) "heading: ", heading

      write (*,*) "ccm: ", ccm

      call s1()
      write (*,*) "alphac: ", alphac

      call s2()

      end program includes

      subroutine s1
C     Subprograms don't inherit from the parent program's implicit declaration?
      implicit none
      write (*,*) "hello from s1"
      write (*,*) "alphac: ", alphac
      end subroutine s1

      subroutine s2
      include "test_header.F"
      write (*,*) "hello from s2"
      write (*,*) "alphac: ", alphac
      end subroutine s2

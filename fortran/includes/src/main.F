      program interfaces
      implicit none

C     Derived from https://docs.oracle.com/cd/E19957-01/805-4939/6j4m0vnaj/index.html

      character heading*(*)
      real epsilon, pi
      logical t

      parameter (epsilon=1.0e-6, pi=3.141593, heading=" IO Error #", t
     $     =.true.)

      include "test_header.F"

      write (*,*) "epsilon: ", epsilon
      write (*,*) "pi: ", pi
      write (*,*) "heading: ", heading

      write (*,*) "ccm: ", ccm

      end program interfaces

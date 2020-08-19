program name
  use fileman_module
  implicit none

  integer :: oper, filenum, datatype, length, offset, offtype

  character :: data_byte
  real (kind=8) :: data_dp
  integer :: data_int
  logical :: data_lgcl

  data_byte = 'f'
  data_dp = 26.3
  data_int = 44
  data_lgcl = .false.

  ! Direct implementation calls
  ! call fileman_byte(oper, filenum, datatype, length, offset, offtype, data_byte)
  ! call fileman_dp(oper, filenum, datatype, length, offset, offtype, data_dp)
  ! call fileman_int(oper, filenum, datatype, length, offset, offtype, data_int)
  ! call fileman_lgcl(oper, filenum, datatype, length, offset, offtype, data_lgcl)

  ! Use the interface defined in the external module
  ! if not set up properly, get linker errors like:
  !
  ! /usr/bin/ld: CMakeFiles/interface_example.x.dir/src/fileman_calls.f90.o: in function `MAIN__':
  ! fileman_calls.f90:(.text+0x59): undefined reference to `fileman_byte_'
  ! /usr/bin/ld: fileman_calls.f90:(.text+0x86): undefined reference to `fileman_dp_'
  ! /usr/bin/ld: fileman_calls.f90:(.text+0xb3): undefined reference to `fileman_int_'
  ! /usr/bin/ld: fileman_calls.f90:(.text+0xe0): undefined reference to `fileman_lgcl_'
  call fileman(oper, filenum, datatype, length, offset, offtype, data_byte)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_dp)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_int)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_lgcl)

end program name

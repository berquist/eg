subroutine fileman_byte (oper, filenum, datatype, length, offset, offtype, data)
  integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
  character, intent(inout) :: data
  write (*,*) "inside fileman_byte"
  write (*,*) data
end subroutine fileman_byte


subroutine fileman_dp (oper, filenum, datatype, length, offset, offtype, data)
  integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
  real (kind=8), intent(inout) :: data
  write (*,*) "inside fileman_dp"
  write (*,*) data
end subroutine fileman_dp


subroutine fileman_int (oper, filenum, datatype, length, offset, offtype, data)
  integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
  integer, intent(inout) :: data
  write (*,*) "inside fileman_int"
  write (*,*) data
end subroutine fileman_int


subroutine fileman_lgcl (oper, filenum, datatype, length, offset, offtype, data)
  integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
  logical, intent(inout) :: data
  write (*,*) "inside fileman_lgcl"
  write (*,*) data
end subroutine fileman_lgcl


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
  call fileman(oper, filenum, datatype, length, offset, offtype, data_byte)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_dp)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_int)
  call fileman(oper, filenum, datatype, length, offset, offtype, data_lgcl)

end program name

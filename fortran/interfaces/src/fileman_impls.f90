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

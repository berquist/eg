module fileman_module

  implicit none

  interface fileman

     subroutine fileman_byte(oper, filenum, datatype, length, offset, offtype, data) bind(C, name="fileman_byte")
       integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
       character, intent(inout) :: data
     end subroutine fileman_byte

     subroutine fileman_dp(oper, filenum, datatype, length, offset, offtype, data) bind(C, name="fileman_dp")
       integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
       real (kind=8), intent(inout) :: data
     end subroutine fileman_dp

     subroutine fileman_int(oper, filenum, datatype, length, offset, offtype, data) bind(C, name="fileman_int")
       integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
       integer, intent(inout) :: data
     end subroutine fileman_int

     subroutine fileman_lgcl(oper, filenum, datatype, length, offset, offtype, data) bind(C, name="fileman_lgcl")
       integer, intent(in) :: oper, filenum, datatype, length, offset, offtype
       logical, intent(inout) :: data
     end subroutine fileman_lgcl

  end interface fileman

end module fileman_module

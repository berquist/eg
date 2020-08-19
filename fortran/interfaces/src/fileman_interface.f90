module fileman_module

  implicit none

  interface fileman

     subroutine fileman_byte(oper, filenum, datatype, length, offset, offtype, data)
       integer :: oper, filenum, datatype, length, offset, offtype
       character :: data
     end subroutine fileman_byte

     subroutine fileman_dp(oper, filenum, datatype, length, offset, offtype, data)
       integer :: oper, filenum, datatype, length, offset, offtype
       real (kind=8) :: data
     end subroutine fileman_dp

     subroutine fileman_int(oper, filenum, datatype, length, offset, offtype, data)
       integer :: oper, filenum, datatype, length, offset, offtype, data
     end subroutine fileman_int

     subroutine fileman_lgcl(oper, filenum, datatype, length, offset, offtype, data)
       integer :: oper, filenum, datatype, length, offset, offtype
       logical :: data
     end subroutine fileman_lgcl

  end interface fileman

end module fileman_module

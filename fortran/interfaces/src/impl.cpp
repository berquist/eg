#include <iostream>

extern "C" void fileman_byte(int *oper, int *filenum, int *datatype, int *length,
                             int *offset, int *offtype, char *data) {
    std::cout << "inside fileman_byte" << std::endl;
    std::cout << *data << std::endl;
}
extern "C" void fileman_dp(int *oper, int *filenum, int *datatype, int *length,
                int *offset, int *offtype, double *data) {
    std::cout << "inside fileman_dp" << std::endl;
    std::cout << *data << std::endl;
}
extern "C" void fileman_int(int *oper, int *filenum, int *datatype, int *length,
                 int *offset, int *offtype, int *data) {
    std::cout << "inside fileman_int" << std::endl;
    std::cout << *data << std::endl;
}
extern "C" void fileman_lgcl(int * oper, int * filenum, int * datatype, int * length, int * offset, int * offtype, bool * data) {
    std::cout << "inside fileman_lgcl" << std::endl;
    std::cout << *data << std::endl;
}

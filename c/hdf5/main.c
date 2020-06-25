#include <stdlib.h>
#include <hdf5.h>

int main() {
    hid_t file_id;
    herr_t status;
    file_id = H5Fcreate("file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    int rank = 2;
    hsize_t * dims = malloc(rank * sizeof(hsize_t));
    dims[0] = 4;
    dims[1] = 6;
    hid_t dataspace_id;
    dataspace_id = H5Screate_simple(rank, dims, NULL);
    hid_t dataset_id;
    dataset_id = H5Dcreate(file_id, "/dset", H5T_STD_I32BE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Dclose(dataset_id);
    status = H5Sclose(dataspace_id);
    status = H5Fclose(file_id);
    free(dims);
    return 0;
}

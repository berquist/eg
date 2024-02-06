/*
 * This program shows how the select_hyperslab and select_elements functions
 * are used to write selected data from memory to the file. Program takes 48
 * elements from the linear buffer and writes them into the matrix using 3x2
 * blocks, (4,3) stride and (2,4) count. Then four elements of the matrix are
 * overwritten with the new values and file is closed. Program reopens the
 * file and reads and displays the result.
 */

#include <iostream>
#include <string>
#include <H5Cpp.h>

using namespace H5;

const H5std_string FILE_NAME("Select.h5");
const H5std_string DATASET_NAME("Matrix in file");
const int MSPACE1_RANK = 1; // Rank of the first dataset in memory
const int MSPACE1_DIM = 50; // Dataset size in memory
const int MSPACE2_RANK = 1; // Rank of the second dataset in memory
const int MSPACE2_DIM = 4; // Dataset size in memory
const int FSPACE_RANK = 2; // Dataset rank as it is stored in the file
const int FSPACE_DIM1 = 8; // Dimension sizes of the dataset as it is stored
                           // in the file
const int FSPACE_DIM2 = 12;
const int MSPACE_RANK = 2; // Rank of the first dataset in memory
const int MSPACE_DIM1 = 8; // We will read dataset back from the file to the
                           // dataset in memory with these
const int MSPACE_DIM2 = 9;
const int NPOINTS = 4; // Number of points that will be selected and
                       // overwritten

int main() {
    int i, j;
    try {
        Exception::dontPrint();
        H5File * file = new H5File(FILE_NAME, H5F_ACC_TRUNC);

        // Create property list for a dataset and set up fill values.
        int fillvalue = 0;
        DSetCreatPropList plist;
        plist.setFillValue(PredType::NATIVE_INT, &fillvalue);

        // Create dataspace for the dataset in the file.
        hsize_t fdim[] = {FSPACE_DIM1, FSPACE_DIM2};
        DataSpace fspace(FSPACE_RANK, fdim);

        // Create dataset and write it into the file.
        DataSet * dataset = new DataSet(file->createDataSet(DATASET_NAME, PredType::NATIVE_INT, fspace, plist));

        // Select hyperslab for the dataset in the file, using 3x2 blocks,
        // (4,3) stride and (2,4) count starting at the position (0,1).
        hsize_t start[2];
        hsize_t stride[2];
        hsize_t count[2];
        hsize_t block[2];
        start[0] = 0; start[1] = 1;
        stride[0] = 4; stride[1] = 3;
        count[0] = 2; count[1] = 4;
        block[0] = 3; block[1] = 2;
        fspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);

        // Create dataspace for the first dataset.
        hsize_t dim1[] = {MSPACE1_DIM};
        DataSpace mspace1(MSPACE1_RANK, dim1);

        // Select hyperslab. We will use 48 elements of the vector buffer
        // starting at the second element. Selected elements are 1 2 3
        // . . . 48
        start[0] = 1;
        stride[0] = 1;
        count[0] = 48;
        block[0] = 1;
        mspace1.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);

        /*
         * Write selection from the vector buffer to the dataset in the file.
         *
         * File dataset should look like this:
         *                    0  1  2  0  3  4  0  5  6  0  7  8
         *                    0  9 10  0 11 12  0 13 14  0 15 16
         *                    0 17 18  0 19 20  0 21 22  0 23 24
         *                    0  0  0  0  0  0  0  0  0  0  0  0
         *                    0 25 26  0 27 28  0 29 30  0 31 32
         *                    0 33 34  0 35 36  0 37 38  0 39 40
         *                    0 41 42  0 43 44  0 45 46  0 47 48
         *                    0  0  0  0  0  0  0  0  0  0  0  0
         */
        int vector[MSPACE1_DIM];
        vector[0] = -1;
        vector[MSPACE1_DIM - 1] = -1;
        for (i = 1; i < MSPACE1_DIM - 1; i++) {
            vector[i] = i;
        }
        dataset->write(vector, PredType::NATIVE_INT, mspace1, fspace);

        // Reset the selection for the file dataspace fid.
        fspace.selectNone();

        // Create dataspace for the second dataset.
        hsize_t dim2[] = {MSPACE2_DIM};
        DataSpace mspace2(MSPACE2_RANK, dim2);

        // Select sequence of NPOINTS points in the file dataspace.
        hsize_t coord[NPOINTS][FSPACE_RANK];
        coord[0][0] = 0; coord[0][1] = 0;
        coord[1][0] = 3; coord[1][1] = 3;
        coord[2][0] = 3; coord[2][1] = 5;
        coord[3][0] = 5; coord[3][1] = 6;
        fspace.selectElements(H5S_SELECT_SET, NPOINTS, (const hsize_t *)coord);

        // Write new selection of points to the dataset.
        int values[] = {53, 59, 61, 67};
        dataset->write(values, PredType::NATIVE_INT, mspace2, fspace);

        /*
         * File dataset should look like this:
         *                   53  1  2  0  3  4  0  5  6  0  7  8
         *                    0  9 10  0 11 12  0 13 14  0 15 16
         *                    0 17 18  0 19 20  0 21 22  0 23 24
         *                    0  0  0 59  0 61  0  0  0  0  0  0
         *                    0 25 26  0 27 28  0 29 30  0 31 32
         *                    0 33 34  0 35 36 67 37 38  0 39 40
         *                    0 41 42  0 43 44  0 45 46  0 47 48
         *                    0  0  0  0  0  0  0  0  0  0  0  0
         *
         */
        delete dataset;
        delete file;
    } catch(FileIException error) {
        error.printErrorStack();
        return -1;
    } catch(DataSetIException error) {
        error.printErrorStack();
        return -1;
    } catch(DataSpaceIException error) {
        error.printErrorStack();
        return -1;
    }
    return 0;
}

find_package(Armadillo)

set(SRC_ARMA
    arma_aniso
    arma_diag
    arma_eye
    arma_fancy_indexing
    arma_sum
    arma_test_mask_index
    arma_test_save
    arma_test_wrap
    arma_test_zero
    class_template
    inv_sqrt
    pointer_cast
    repack
    schur_matrix_vector
    timing
    )

if(${ARMADILLO_FOUND})
    message(STATUS "SRC_ARMA: ${SRC_ARMA}")
    foreach(file ${SRC_ARMA})
        add_executable(${file}.x ${file}.cpp)
        target_link_libraries(${file}.x ${ARMADILLO_LIBRARIES})
    endforeach(file)
endif()

add_subdirectory(class_template_2)

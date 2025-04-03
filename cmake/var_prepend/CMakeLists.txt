cmake_minimum_required(VERSION 3.10)
project(var_prepend LANGUAGES NONE)

set(SRC
    configurable.C
    dump_ao_integrals.C
    index_printing.C
    indices.C
    matvec_i.C
    utils.C
    linear/helpers.C
    linear/interface.C
    linear/interface_nonorthogonal.C
    linear/printing.C
    operator_spec.C
    set_defaults.C
    )

message(STATUS "SRC: ${SRC}")

# https://stackoverflow.com/a/27630120
function(PREPEND var prefix files)
    set(tmpvar "")
    # Can't quote ${files}; that gives the ;-string!
    foreach(file ${files})
        # message(STATUS "file: ${file}")
        list(APPEND tmpvar "${prefix}/${file}")
    endforeach(file)
    set("${var}" "${tmpvar}" PARENT_SCOPE)
endfunction(PREPEND)

prepend(SRC_LIBRESPONSE libresponse "${SRC}")
message(STATUS "SRC_LIBRESPONSE: ${SRC_LIBRESPONSE}")

# -*- mode: autoconf; -*-
AC_DEFUN([SET_COMPILER_FLAGS], [dnl
  AC_LANG_PUSH([C++])
  AX_COMPILER_VENDOR
  AC_LANG_POP([C++])

  AS_IF([test "$ax_cv_cxx_compiler_vendor" = "clang"],
        [COMPILER_FLAGS_2="hello5"],
        [COMPILER_FLAGS_2="world5"])
  AC_SUBST([COMPILER_FLAGS_2])
])dnl

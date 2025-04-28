AC_INIT([My Project], [1.0])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CXX
dnl AC_LANG_PUSH([C++])
dnl AX_COMPILER_VENDOR
dnl AC_LANG_POP([C++])

dnl # configure time
dnl case "$ax_cv_cxx_compiler_vendor" in
dnl     clang)
dnl         echo "hello"
dnl         ;;
dnl     *)
dnl         echo "world"
dnl         ;;
dnl esac

dnl # configure time
dnl if test "$ax_cv_cxx_compiler_vendor" = "clang"; then
dnl     echo "hello2"
dnl else
dnl     echo "world2"
dnl fi

dnl # generates the above portably during autoreconf and runs the result at
dnl # configure time
dnl AS_IF([test "$ax_cv_cxx_compiler_vendor" = "clang"],
dnl       [echo "hello3"],
dnl       [echo "world3"])

dnl AS_IF([test "$ax_cv_cxx_compiler_vendor" = "clang"],
dnl       [COMPILER_FLAGS="hello4"],
dnl       [COMPILER_FLAGS="world4"])
dnl AC_SUBST([COMPILER_FLAGS])

SET_COMPILER_FLAGS

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

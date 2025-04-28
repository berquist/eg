AC_INIT([My Project], [1.0])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CXX
AC_LANG_PUSH([C++])
AX_COMPILER_VENDOR
AC_LANG_POP([C++])
AC_CACHE_SAVE

# configure time
case "$ax_cv_cxx_compiler_vendor" in
    clang)
        echo "hello"
        ;;
    *)
        echo "world"
        ;;
esac

# configure time
if test "$ax_cv_cxx_compiler_vendor" = "clang"; then
    echo "hello2"
else
    echo "world2"
fi

# generates the above portably during autoreconf and runs the result at
# configure time
AS_IF([test "$ax_cv_cxx_compiler_vendor" = "clang"],
      [echo "hello3"],
      [echo "world3"])

AS_IF([test "$ax_cv_cxx_compiler_vendor" = "clang"],
      [COMPILER_FLAGS="hello4"],
      [COMPILER_FLAGS="world4"])
AC_SUBST([COMPILER_FLAGS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

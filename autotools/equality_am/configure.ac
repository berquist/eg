AC_INIT([My Project], [1.0])
AM_INIT_AUTOMAKE([foreign])
MY_VARIABLE=some_value
AC_SUBST([MY_VARIABLE])
if test "$MY_VARIABLE" = "some_value"; then
    AC_SUBST([EXTRA_DIST_FILES], ["file1.txt file2.txt"])
else
    AC_SUBST([EXTRA_DIST_FILES], ["file3.txt"])
fi
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

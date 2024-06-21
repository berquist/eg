include(`m4sugar/m4sugar.m4')m4_init[]m4_divert([0])dnl
dnl
m4_define([_m4_remove_lib_prefix],
[m4_bpatsubst($1,^-l,)])dnl
dnl
_m4_remove_lib_prefix([-lncurses])
_m4_remove_lib_prefix([-lmy-lib])
m4_map_sep([_m4_remove_lib_prefix], [ ], [[-lncurses], [-lmy-lib]])
m4_map_sep([_m4_remove_lib_prefix], [ ], m4_split([-lncurses -lmy-lib]))
# m4_define([m4_remove_lib_prefix],m4_map_sep([_m4_remove_lib_prefix], [ ], m4_split(m4_expand($1))))dnl
# m4_remove_lib_prefix([-lncurses -lmy-lib])
#m4_define([m4_remove_lib_prefix],m4_map_sep([_m4_remove_lib_prefix], [ ], $1))dnl
# m4_define([m4_remove_lib_prefix],m4_mapall([_m4_remove_lib_prefix], m4_unquote($1)))dnl
# m4_remove_lib_prefix([[-lncurses] [-lmy-lib]])

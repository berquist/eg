include(`m4sugar/m4sugar.m4')m4_init[]m4_divert([0])dnl
m4_define([_m4_remove_lib_prefix],
[m4_bpatsubst($1,^-l,)])dnl
dnl
_m4_remove_lib_prefix([-lncurses])
_m4_remove_lib_prefix([-lmy-lib])
m4_map_sep([_m4_remove_lib_prefix], [ ], [[-lncurses], [-lmy-lib]])
m4_map_sep([_m4_remove_lib_prefix], [ ], m4_split([-lncurses -lmy-lib]))
m4_define([m4_remove_lib_prefixes_list],
[m4_map_sep([_m4_remove_lib_prefix], [ ], [$1])])dnl
m4_remove_lib_prefixes_list([[-lncurses], [-lmy-lib]])
m4_define([m4_remove_lib_prefixes_str],
[m4_map_sep([_m4_remove_lib_prefix], [ ], m4_split([$1]))])dnl
m4_remove_lib_prefixes_str([-lncurses -lmy-lib])

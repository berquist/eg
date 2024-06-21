include(`m4sugar/m4sugar.m4')m4_init[]m4_divert([0])dnl
dnl this works
m4_reverse([hello], [world])
dnl this does not work
m4_reverse([[hello], [world]])

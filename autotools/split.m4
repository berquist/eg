include(`m4sugar/m4sugar.m4')m4_init[]m4_divert([0])dnl
ac_elements_flags="apple,pear,cherry"
echo "ac_elements_flags: $ac_elements_flags"
m4_split(ac_elements_flags, ",")

define(M, N)dnl
echo M
echo N
define(N, 100)dnl
echo M
echo N
define(`N', 200)dnl
echo M
echo N
dnl
ifdef(`unix', on UNIX, not on UNIX)
dnl
define(bump, $1 = $1 + 1)dnl
bump(x)
define(N1, `incr(N)')dnl
N1
This doesn't make any sense, but we can do it anyway: bump(N1)
syscmd(date)dnl
define(compare, `ifelse($1, $2, yes, no)')dnl
compare(hi, bye)
compare(apple, apple)

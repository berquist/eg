foo = hello

.PHONY: using-variables
using-variables:
	: "WRONG"
	echo $foo
	: "WRONG: the shell variable (via escaped $$)"
	echo $$foo
	: "CORRECT: the Make variable"
	echo $(foo)

# if foo == "hello"

# endif

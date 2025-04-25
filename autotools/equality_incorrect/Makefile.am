foo = hello

.PHONY: using-variables
using-variables:
	: "WRONG: only the first character after $$ is interpreted as the Make variable name"
	echo $foo
	: "WRONG: the shell variable (via escaped $$)"
	echo $$foo
	: "CORRECT: the Make variable"
	echo $(foo)

if foo == "hello"
	echo "true"
else
	echo "false"
endif

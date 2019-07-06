.PHONY: build_c
build_c:
	gcc --std=c11 -o c-example.x src/main.c -L target/debug -lrust

.PHONY: run_c
run_c: build_c
	LD_LIBRARY_PATH=target/debug:$LD_LIBRARY_PATH ./c-example.x

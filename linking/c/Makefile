.PHONY: build_c
build_c:
	mkdir -p build && cd build && cmake .. && make && cd ..

.PHONY: build_cython
build_cython:
	python setup.py build_ext -i

.PHONY: run_cython
run_cython: build_cython
	LD_LIBRARY_PATH=./build:$LD_LIBRARY_PATH python using_cython_example.py

.PHONY: build_rust
build_rust:
	cd rust && cargo build && cd ..

.PHONY: run_rust
run_rust: build_rust
	cd rust && LD_LIBRARY_PATH=../build:$LD_LIBRARY_PATH cargo run && cd ..

.PHONY: clean
clean:
	git clean -xdf .

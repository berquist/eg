.PHONY: build_c
build_c:
	mkdir -p build && cd build && cmake .. && make && cd ..

.PHONY: build_cython
build_cython:
	python setup.py build_ext -i

.PHONY: clean
clean:
	git clean -xdf .

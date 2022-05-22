.PHONY: greetings
greetings: greetings.nim
	nim r greetings.nim

.PHONY: greetings-release
greetings-release: greetings.nim
	nim r -d:release greetings.nim

.PHONY: tutorial_1
tutorial_1: tutorial_1.nim
	nim r --listCmd tutorial_1.nim

.PHONY: tutorial_1_modules
tutorial_1_modules: tutorial_1_modules.nim
	nim r --listCmd tutorial_1_modules.nim
	nim r --listCmd C.nim

.PHONY: fftw
fftw: fftw.nim
	nim r fftw.nim

.PHONY: complex_numbers
complex_numbers: complex_numbers.nim
	nim r complex_numbers.nim

.PHONY: all
all: greetings greetings-release tutorial_1 tutorial_1_modules fftw complex_numbers

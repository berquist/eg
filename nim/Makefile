greetings: greetings.nim
	nim compile --run greetings.nim

greetings-release: greetings.nim
	nim c -d:release --run greetings.nim

tutorial_1: tutorial_1.nim
	nim c -r --listCmd tutorial_1.nim

tutorial_1_modules: tutorial_1_modules.nim
	nim c -r --listCmd tutorial_1_modules.nim
	nim c -r --listCmd C.nim

fftw: fftw.nim
	nim c -r fftw.nim

from complex import Complex64, complex64
from sequtils import map
from sugar import `=>`
import fftw3

proc nim_to_fftw(inp: Complex64): fftw_complex =
  [inp.re, inp.im]

proc fftw_to_nim(inp: fftw_complex): Complex64 =
  complex64(inp[0], inp[1])

proc nim_to_fftw(inp: openArray[Complex64]): seq[fftw_complex] =
  inp.map(v => nim_to_fftw(v))

proc fftw_to_nim(inp: openArray[fftw_complex]): seq[Complex64] =
  inp.map(v => fftw_to_nim(v))

when isMainModule:
  let cx1: array[2, cdouble] = [2.0, 3.0]
  echo cx1
  echo repr(cx1)
  let cx2: fftw_complex = [2.0, 3.0]
  assert(cx1 == cx2)
  let cx3 = complex64(2.0, 3.0)
  assert(cx3 == fftw_to_nim(nim_to_fftw(cx3)))
  let cs1 = @[cx3, complex64(4.0, 5.0), complex64(-1.0, -1.0)]
  assert(cs1 == fftw_to_nim(nim_to_fftw(cs1)))

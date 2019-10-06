# Module A
var
  x*, y: int

proc `*` *(a, b: seq[int]): seq[int] =
  newSeq(result, len(a))
  for i in 0..len(a) - 1:
    result[i] = a[i] * b[i]

when isMainModule:
  # test the new ``*`` operator for sequences:
  assert(@[1, 2, 3] * @[1, 2, 3] == @[1, 4, 9])

import arraymancer
import random

proc fill_rand[T](t: var Tensor[T], val: T) =
  doAssert t.shape.len == 2
  for i in 0..<t.shape[0]:
    for j in 0..<t.shape[1]:
      t[i, j] = rand(val)

when isMainModule:
  var t = @[@[1.0, 1.1, 1.2],
            @[2.1, 4.3, 3.3],
            @[1.3, 1.4, 1.5]].toTensor()
  echo t
  t.fill_rand(1.0)
  echo t

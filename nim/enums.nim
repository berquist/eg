type
  Opcode = enum
    add = 1
    multiply = 2
    input = 3
    output = 4
    jumpIfTrue = 5
    jumpIfFalse = 6
    lessThan = 7
    equals = 8
    halt = 99
  # Opcode = enum
  #   add = (1, 4)
  #   multiply = (2, 4)
  #   input = (3, 2)
  #   output = (4, 2)
  #   jumpIfTrue = (5, 3)
  #   jumpIfFalse = (6, 3)
  #   lessThan = (7, 4)
  #   equals = (8, 4)
  #   halt = (99, 1)

proc len(oc: Opcode): int =
  case oc:
    of add: 4
    of multiply: 4
    of input: 2
    of output: 2
    of jumpIfTrue: 3
    of jumpIfFalse: 3
    of lessThan: 4
    of equals: 4
    of halt: 1

when isMainModule:
  echo Opcode
  echo Opcode.jumpIfTrue
  echo ord(Opcode.jumpIfTrue)
  echo Opcode.jumpIfTrue.ord
  echo Opcode(99) == Opcode.halt
  echo Opcode(6) == Opcode.jumpIfFalse
  # echo Opcode(10)

  echo len(Opcode.jumpIfFalse)
  echo Opcode.jumpIfFalse.len

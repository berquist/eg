# https://nim-lang.org/docs/tut1.html

# A comment.
var myVariable: int ## A documentation comment.

#[
You can have any Nim code text commented
out inside this with no restrictions.
      yes("May I ask a pointless question?")
  #[
     Note: these can be nested!!
  ]#
]#


discard """You can have any Nim code text commented
out inside this with no indentation restrictions.
      yes("May I ask a pointless question?")"""

#[
var x, y: int # declares x and y to have the type ``int``

var
  x, y: int
  # a comment can occur here too
  a, b, c: string

var x = "abc"
echo x
x = "xyz"
echo x

const
  x = 1
  # a comment can occur here too
  y = 2
  z = y + 5 # computations are possible

let name = readLine(stdin)
if name == "":
  echo "Poor soul, lost your name?"
elif name == "name":
  echo "Very funny, your name is name."
else:
  echo "Hi, ", name, "!"

let name2 = readLine(stdin)
case name2
of "":
  echo "Poor soul, you lost your name?"
of "name":
  echo "Very funny, your name is name."
of "Dave", "Frank":
  echo "Cool name!"
else:
  echo "Hi, ", name, "!"

# this statement will be explained later:
from strutils import parseInt

echo "A number please: "
let n = parseInt(readLine(stdin))
case n
nof 0..2, 4..7: echo "The number is in the set {0, 1, 2, 4, 5, 6, 7}"
of 3, 8: echo "The number is 3 or 8"
else: discard
]#

echo "Counting to ten:"
for i in countup(1, 10):
  echo i

echo "Counting down from 10 to 1:"
for i in countdown(10, 1):
  echo i

for index, item in ["a", "b"].pairs:
  echo item, " at index ", index

when system.hostOS == "windows":
  echo "running on Windows!"
elif system.hostOS == "linux":
  echo "running on Linux!"
elif system.hostOS == "macosx":
  echo "running on macOS!"
else:
  echo "unknown operating system: ", system.hostOS

# https://nim-lang.org/docs/tut1.html#procedures-result-variable
proc sumTillNegative(x: varargs[int]): int =
  for i in x:
    if i < 0:
      return
    result = result + i

echo sumTillNegative() # echoes 0
echo sumTillNegative(3, 4, 5) # echoes 12
echo sumTillNegative(3, 4, -1, 6) # echoes 7

proc printSeq(s: seq, nprinted: int = -1) =
  var nprinted = if nprinted == -1: s.len else: min(nprinted, s.len)
  for i in 0..<nprinted:
    echo s[i]

# If the procedure needs to modify the argument for the caller, a `var`
# parameter can be used:
proc divmod(a, b: int; res, remainder: var int) =
  res = a div b       # integer division
  remainder = a mod b # integer modulo operation

var
  x, y: int
divmod(8, 5, x, y) # modifies x and y
echo x
echo y

proc p(x, y: int): int {.discardable.} =
  x + y

p(3, 4)
echo p(3, 4)

# forward declaration:
proc even(n: int): bool

proc odd(n: int): bool =
  assert(n >= 0) # makes sure we don't run into negative recursion
  if n == 0: false
  else:
    n == 1 or even(n - 1)

proc even(n: int): bool =
  assert(n >= 0) # makes sure we don't run into negative recursion
  if n == 1: false
  else:
    n == 0 or odd(n - 1)

iterator countup(a, b: int): int =
  var res = a
  while res <= b:
    yield res
    inc(res)

echo "--- repr(...) ---"
var
  myBool = true
  myCharacter = 'n'
  myString = "nim"
  myInteger = 42
  myFloat = 3.14
echo myBool, ":", repr(myBool)
echo myCharacter, ":", repr(myCharacter)
echo myString, ":", repr(myString)
echo myInteger, ":", repr(myInteger)
echo myFloat, ":", repr(myFloat)

type
  Direction = enum
    north, east, south, west

var x2 = south  # `x2` is of type `Direction`; its value is `south`
echo x2         # writes "south" to `stdout`
echo Direction.north
echo ord(Direction.north), " ",
    ord(Direction.east), " ",
    ord(Direction.south), " ",
    ord(Direction.west)
echo succ(23)

type
  MyRange = range[0..5]

type
  CharSet = set[char]
var
  x3: CharSet
x3 = {'a'..'z', '0'..'9'} # This constructs a set that contains the letters
                          # from 'a' to 'z' and the digits from '0' to '9'
echo x3
echo repr(x3)
echo card(x3)

# bit fields
type
  MyFlag* {.size: sizeof(cint).} = enum
    A
    B
    C
    D
  MyFlags = set[MyFlag]

proc toNum(f: MyFlags): int = cast[cint](f)
proc toFlags(v: int): MyFlags = cast[MyFlags](v)
assert toNum({}) == 0
assert toNum({A}) == 1
assert toNum({B}) == 2
assert toNum({C}) == 4
assert toNum({D}) == 8
assert toFlags(0) == {}
assert toFlags(1) == {A}
assert toFlags(7) == {A, B, C}

type
  IntArray = array[0..5, int] # an array that is indexed with 0..5
var
  x4: IntArray
x4 = [1, 2, 3, 4, 5, 6]
for i in low(x4)..high(x4):
  echo x4[i]

type
  BlinkLights = enum
    off, on, slowBlink, mediumBlink, fastBlink
  LevelSetting = array[north..west, BlinkLights]
var
  level: LevelSetting
level[north] = on
level[south] = slowBlink
level[east] = fastBlink
echo level

# using an explicitly nested array type instead
type
  LightTower = array[1..10, array[north..west, BlinkLights]]

type
  # IntArray = array[0..5, int] # an array that is indexed with 0..5
  QuickArray = array[6, int]  # an array that is indexed with 0..5
var
  x5: IntArray
  y5: QuickArray
x5 = [1, 2, 3, 4, 5, 6]
y5 = x5
for i in low(x5)..high(x5):
  echo x5[i], " ", y5[i]

# sequences
for value in @[3, 4, 5]:
  echo value
for i, value in @[3, 4, 5]:
  echo "index: ", i, " value: ", value

var
  fruits: seq[string]         # reference to a sequence of strings that is initialized with '@[]'
  capitals: array[3, string]  # array of strings with a fixed size
capitals = ["New York", "London", "Berlin"]
fruits.add("Banana")
fruits.add("Mango")

proc openArraySize(oa: openArray[string]): int =
  oa.len

assert openArraySize(capitals) == 3
assert openArraySize(fruits) == 2

# proc myWriteln(f: File, a: varargs[string]) =
#   for s in items(a):
#     write(f, s)
#   write(f, "\n")

# myWriteln(stdout, "abc", "def", "xyz")

proc myWriteln(f: File, a: varargs[string, `$`]) =
  for s in items(a):
    write(f, s)
  write(f, "\n")

myWriteln(stdout, 123, "def", 4.0)

var
  a = "Nim is a programming language"
  #              111111111
  #    0123456789012345678
  b = "Slices are useless."
assert a[7..12] == "a prog"
b[11..^2] = "useful"
assert b == "Slices are useful."

type
  Person = object
    name: string
    age: int

var person1 = Person(name: "Peter", age: 30)
echo person1
var person2 = person1
person2.age += 14
let person3 = Person(age: 12, name: "Quentin")
echo person3
# not every member needs to be specified
let person4 = Person(age: 3)
# Unspecified members will be initialized with their default values.
doAssert person4.name == ""
assert person4.name == ""
# What's the difference between `assert` and `doAssert`?

type
  Person2* = object # the type is visible from other modules
    name*: string   # the field of this type is visible from other modules
    age: int        # the field of this type is _not_ visible from other modules

type
  Person3 = tuple
    name: string
    age: int

  # Alternative syntax for an equivalent type.
  PersonX = tuple[name: string, age: int]

  # anonymous syntax
  PersonY = (string, int)

var
  personT1: Person3
  personT2: PersonX
  personT3: PersonY
personT1 = (name: "Peter", age: 30)
# Person3 and PersonX are equivalent
personT2 = personT1
# Create a tuple with anonymous fields:
personT3 = ("Peter", 30)
# A tuple with anonymous fields is compatible with a tuple that has field
# names.
personT1 = personT3
personT3 = personT1

# You don't need to declare tuples in a separate type section.
var building: tuple[street: string, number: int]
building = ("Rue de Percebe", 13)
echo building

# The following line doesn't compile because they're structurally different,
# despite both being tuples.
# personT1 = building
# type mismatch: got <tuple[street: string, number: int]> but expected 'Person3 = tuple[name: string, age: int]'

import os

let
  path = "usr/local/nimc.html"
  (dir, name, ext) = splitFile(path)
  baddir, badname, badext = splitFile(path)
echo dir
echo name
echo ext
echo baddir
echo badname
echo badext

type
  Node = ref object
    le, ri: Node
    data: int
var
  n: Node
new(n)
n.data = 9
echo repr(n)

proc echoItem(x: int) = echo x

proc forEach(action: proc (x: int)) =
  const
    data = [2, 3, 5, 7, 11]
  for d in items(data):
    action(d)

forEach(echoItem)

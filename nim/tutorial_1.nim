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
]#

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
of 0..2, 4..7: echo "The number is in the set {0, 1, 2, 4, 5, 6, 7}"
of 3, 8: echo "The number is 3 or 8"
else: discard

echo "Counting to ten: "
for i in countup(1, 10):
  echo i

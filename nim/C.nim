import A, B

# Error: ambiguous identifier: 'x' -- use one of the following:
#   A.x: string
#   B.x: int
# write(stdout, x)
write(stdout, A.x) # okay: qualifier used

var x = 4
write(stdout, x) # not ambiguous: uses the module C's x

write(stdout, x2(3))       # no error: A.x2 is called
write(stdout, x2("meep"))  # no error: B.x2 is called
proc x2*(a: int): string = discard
write(stdout, x2(3))

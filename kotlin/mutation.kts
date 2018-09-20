val fruits = listOf("apple", "banana", "pear")
(fruits as MutableList)[1] = "kumquat"
println(fruits)
assert(fruits == listOf("apple", "kumquat", "pear"))

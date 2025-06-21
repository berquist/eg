using LinearAlgebra

mat = [
    -0.386087 0.00813956 0.0781361;
    0.00813956 -0.390147 0.0986476;
    0.0781361 0.0986476 0.776234;
]
e = eigen(mat)
println(e.values)
println(e.vectors)

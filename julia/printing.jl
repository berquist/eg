# https://discourse.julialang.org/t/how-to-print-field-names-and-values-in-a-struct/5892

struct MyStruct
    x::Int
    y::String
end

a = MyStruct(5, "hello")
b = MyStruct(9, "world")
println(a)
println(b)
println(fieldnames(MyStruct))

function Base.show(io::IO, s::MyStruct)
    for fieldname in fieldnames(typeof(s))
        println(io, "$fieldname = $(getfield(s, fieldname))")
    end
end

println(a)
println(b)

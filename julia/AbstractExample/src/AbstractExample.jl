module AbstractExample

export
    Object,
    Group,
    File,
    create_group

abstract type AbstractObject end
abstract type AbstractGroup <: AbstractObject end
abstract type AbstractFile <: AbstractGroup end

struct Object <: AbstractObject
    x::Int
end

struct Group <: AbstractGroup
    y::Int
end

struct File <: AbstractFile
    z::Int
end

function create_group(x)
    println("hello")
end

function create_group(x::AbstractObject)
    println("world $x")
end

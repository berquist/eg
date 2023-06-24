using AbstractExample
using Documenter

DocMeta.setdocmeta!(AbstractExample, :DocTestSetup, :(using AbstractExample); recursive=true)

makedocs(;
    modules=[AbstractExample],
    authors="Eric Berquist <eric.berquist@gmail.com> and contributors",
    repo="https://github.com/berquist/AbstractExample.jl/blob/{commit}{path}#{line}",
    sitename="AbstractExample.jl",
    format=Documenter.HTML(;
        prettyurls=get(ENV, "CI", "false") == "true",
        canonical="https://berquist.github.io/AbstractExample.jl",
        edit_link="main",
        assets=String[],
    ),
    pages=[
        "Home" => "index.md",
    ],
)

deploydocs(;
    repo="github.com/berquist/AbstractExample.jl",
    devbranch="main",
)

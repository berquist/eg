#!/usr/bin/env sh

julia --project=docs -e '
  using Documenter: DocMeta, doctest
  using AbstractExample
  DocMeta.setdocmeta!(AbstractExample, :DocTestSetup, :(using AbstractExample); recursive=true)
  doctest(AbstractExample)'

{ pkgs ? import <nixpkgs> {} }:
with pkgs;

stdenv.mkDerivation {
  name = "eg";
  buildInputs = [
    armadillo
    cmake
    hdf5
    highfive
  ];
}

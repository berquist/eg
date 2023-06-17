fn main() {
    cxx_build::bridge("src/lib.rs")
        .file("src/wrapper.cpp")
        .flag_if_supported("-std=c++14")
        .compile("test-cxx");

    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=src/wrapper.cpp");
    println!("cargo:rerun-if-changed=include/wrapper.hpp");
}

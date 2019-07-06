extern crate libc;

use libc::c_int;

#[link(name = "mylib")]
extern "C" {
    fn add1(x: c_int) -> c_int;
}

fn main() {
    println!("{}", unsafe { add1(3) });
}

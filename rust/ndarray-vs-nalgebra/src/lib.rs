extern crate nalgebra as na;
use na::Matrix4;
use ndarray::{Array, Ix2};

pub fn add1_ret(m: &Array<f64, Ix2>) -> Array<f64, Ix2> {
    let shape = m.shape();
    Array::ones((shape[0], shape[1])) + m
}

pub fn add1_part_mut(m: &mut Array<f64, Ix2>) {
    let shape = m.shape();
    *m += &Array::ones((shape[0], shape[1]));
}

pub fn perform_add_nalgebra(a: &Matrix4<u64>, b: &Matrix4<u64>) -> Matrix4<u64> {
    a + b
}

pub fn perform_add_ndarray(a: &Array<u64, Ix2>, b: &Array<u64, Ix2>) -> Array<u64, Ix2> {
    a + b
}

pub fn perform_add_mut_nalgebra(a: &mut Matrix4<u64>, b: &Matrix4<u64>, c: &Matrix4<u64>) {
    *a += b + c;
}

pub fn perform_add_mut_ndarray(a: &mut Array<u64, Ix2>, b: &Array<u64, Ix2>, c: &Array<u64, Ix2>) {
    *a = b + c;
}

pub fn perform_add_box_nalgebra(a: &Box<Matrix4<f64>>, b: &Box<Matrix4<f64>>) -> Box<Matrix4<f64>> {
    Box::new(**a + **b)
}

pub fn perform_add_mut_inplace_nalgebra(a: &mut Matrix4<f64>, b: &Matrix4<f64>) {
    *a += b;
}

pub fn perform_add_mut_inplace_ndarray(a: &mut Array<u64, Ix2>, b: &Array<u64, Ix2>) {
    *a += b;
}

pub fn perform_add_ndarray_float(a: &Array<f64, Ix2>, b: &Array<f64, Ix2>) -> Array<f64, Ix2> {
    a + b
}

// TODO const generics?
pub fn perform_add_mut_inplace_ndarray_float(a: &mut Array<f64, Ix2>, b: &Array<f64, Ix2>) {
    *a += b;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let dim = 10;
        let m1: Array<f64, _> = Array::ones((dim, dim));
        println!("m1: {:?}", add1_ret(&m1));

        let mut m2: Array<f64, _> = Array::ones((dim, dim));
        println!("m2 before: {:?}", m2);
        add1_part_mut(&mut m2);
        println!("m2 after: {:?}", m2);
    }
}

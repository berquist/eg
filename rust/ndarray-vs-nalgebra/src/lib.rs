extern crate nalgebra as na;
use na::Matrix4;
use ndarray::{Array, Ix2};

pub fn add1_ret(m: &Array<f64, Ix2>) -> Array<f64, Ix2> {
    let shape = m.shape();
    Array::ones((shape[0], shape[1])) + m
}

pub fn add1_part_mut(m: &mut Array<f64, Ix2>) {
    let shape = m.shape();
    let mut ones: Array<f64, _> = Array::ones((shape[0], shape[1]));
    // m += ones;
    // m = m + &mut ones;
    // m = &mut (ones + m);
    // m = &mut ones;

    // WHY DOESN'T THIS WORK
    // m = &mut ones + m;

    // m.fill(2.0);

    // let mc = m.clone();
    // m = &mut (mc + ones);

    // *m = m + ones;
    // let vm = m.view();
    // vm = vm + ones.view();
    // println!("{}", vm);
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let dim = 10;
        // let m1: Array<f64, _> = Array::ones((dim, dim));
        // println!("{:?}", add1_ret(&m1));

        let mut m2: Array<f64, _> = Array::ones((dim, dim));
        println!("{:?}", m2);
        add1_part_mut(&mut m2);
        println!("{:?}", m2);

        // let cm3 = RefCell::new(Array::ones((dim, dim)));
        // add_1_refcell(&cm3);
        // println!("{:?}", cm3);
    }
}

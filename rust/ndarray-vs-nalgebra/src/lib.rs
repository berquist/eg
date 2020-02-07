// use std::cell::RefCell;

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

// pub fn add_1_refcell(m: &RefCell<Array<f64, Ix2>>) {
//     let x = m.borrow_mut();
//     // println!("{}", x);
//     let shape = *x.shape();
//     *x = *x + Array::ones((shape[0], shape[1]));
// }

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

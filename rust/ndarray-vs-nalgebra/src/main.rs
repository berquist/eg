// use std::ops::Add;

extern crate nalgebra as na;
use na::Matrix4;
use ndarray::{Array, Ix2};

fn main() {
    let dim = 4;

    let m1 = Matrix4::new(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    let m2 = m1 * 2;

    let nd1 = ndarray::array![
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16]
    ];
    let nd2 = &nd1 * 2;

    perform_add_nalgebra(&m1, &m2);
    perform_add_ndarray(&nd1, &nd2);

    let mut m3 = Matrix4::zeros();
    m3 = m1 + m2;
    println!("{}", m3);
    perform_add_mut_nalgebra(&mut m3, &m2, &m2);
    println!("{}", m3);

    let mut nd3 = Array::zeros((dim, dim));
    nd3 = &nd2 + &nd1;
    println!("{}", nd3);
    perform_add_mut_ndarray(&mut nd3, &nd2, &nd2);
    println!("{}", nd3);

    // let m4: Box<Matrix4<u64>> = Box::new(Matrix4::zeros());
    // let nd4: Box<Array<u64, Ix2>> = Box::new(Array::zeros((dim, dim)));
    let bm1: Box<Matrix4<f64>> = Box::new(Matrix4::new_random());
    let bm2: Box<Matrix4<f64>> = Box::new(Matrix4::new_random());
    let bm3 = perform_add_box_nalgebra(&bm1, &bm2);
    println!("{}", bm1);
    println!("{}", bm2);
    println!("{}", bm3);

    // Try doing stuff in place.
    let mut m4 = Matrix4::new_random();
    println!("{}", m4);
    // m4 += *bm3;
    perform_add_mut_inplace_nalgebra(&mut m4, &*bm3);
    println!("{}", m4);
    let mut nd4: Array<u64, _> = Array::ones((dim, dim));
    println!("{}", nd4);
    // This line doesn't work
    // nd4 += nd1;
    // nd4 = nd4 + nd1;
    perform_add_mut_inplace_ndarray(&mut nd4, &nd3);
    println!("{}", nd4);
}

// fn perform_add<T: Add>(a: &T, b: &T) -> T {
//     return a + b;
// }

fn perform_add_nalgebra(a: &Matrix4<u64>, b: &Matrix4<u64>) -> Matrix4<u64> {
    a + b
}

fn perform_add_ndarray(a: &Array<u64, Ix2>, b: &Array<u64, Ix2>) -> Array<u64, Ix2> {
    a + b
}

fn perform_add_mut_nalgebra(a: &mut Matrix4<u64>, b: &Matrix4<u64>, c: &Matrix4<u64>) {
    *a += b + c;
}

fn perform_add_mut_ndarray(a: &mut Array<u64, Ix2>, b: &Array<u64, Ix2>, c: &Array<u64, Ix2>) {
    *a = b + c;
}

fn perform_add_box_nalgebra(a: &Box<Matrix4<f64>>, b: &Box<Matrix4<f64>>) -> Box<Matrix4<f64>> {
    Box::new(**a + **b)
}

fn perform_add_mut_inplace_nalgebra(a: &mut Matrix4<f64>, b: &Matrix4<f64>) {
    // *a += b;
    *a = *a + b;
}

fn perform_add_mut_inplace_ndarray(a: &mut Array<u64, Ix2>, b: &Array<u64, Ix2>) {
    // *a = *a + b;
}

#[macro_use]
extern crate criterion;

use criterion::Criterion;

extern crate nalgebra as na;
use na::Matrix4;
use ndarray::{Array, Ix2};

use test_ndarray::{add1_mut, add1_ret};

fn perform_add_nalgebra(a: &Matrix4<u64>, b: &Matrix4<u64>) -> Matrix4<u64> {
    a + b
}

fn perform_add_ndarray(a: &Array<u64, Ix2>, b: &Array<u64, Ix2>) -> Array<u64, Ix2> {
    a + b
}

fn perform_add_mut_nalgebra(a: &mut Matrix4<u64>, b: &Matrix4<u64>, c: &Matrix4<u64>) {
    *a = b + c;
}

fn perform_add_mut_ndarray(a: &mut Array<u64, Ix2>, b: &Array<u64, Ix2>, c: &Array<u64, Ix2>) {
    *a = b + c;
}

fn perform_add_box_nalgebra(a: &Box<Matrix4<f64>>, b: &Box<Matrix4<f64>>) -> Box<Matrix4<f64>> {
    Box::new(**a + **b)
}

fn criterion_benchmark(c: &mut Criterion) {
    let dim = 10;
    let m1: Array<f64, _> = Array::ones((dim, dim));
    let mut m2: Array<f64, _> = Array::ones((dim, dim));
    // println!("{:?}", add1_ret(&m1));
    // add1_mut(&mut m2);
    // println!("{:?}", m2);

    c.bench_function("add1_ret", move |b| b.iter(|| add1_ret(&m1)));
    c.bench_function("add1_mut", move |b| b.iter(|| add1_mut(&mut m1)));

    let m1 = Matrix4::new(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    let m2 = m1 * 2;
    let nd1 = ndarray::array![
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16]
    ];
    let nd2 = &nd1 * 2;
    let mut m3 = Matrix4::zeros();
    let dim = 4;
    let mut nd3: Array<u64, Ix2> = ndarray::Array::zeros((dim, dim));
    let bm1: Box<Matrix4<f64>> = Box::new(Matrix4::new_random());
    let bm2: Box<Matrix4<f64>> = Box::new(Matrix4::new_random());
    c.bench_function("perform_add_nalgebra", move |b| {
        b.iter(|| black_box(perform_add_nalgebra(&m1, &m2)))
    });
    // c.bench_function("perform_add_ndarray", move |b| {
    //     b.iter(|| black_box(perform_add_ndarray(&nd1, &nd2)))
    // });
    c.bench_function("perform_add_mut_nalgebra", move |b| {
        b.iter(|| black_box(perform_add_mut_nalgebra(&mut m3, &m2, &m2)))
    });
    c.bench_function("perform_add_mut_ndarray", move |b| {
        b.iter(|| perform_add_mut_ndarray(&mut nd3, &nd2, &nd2))
    });
    c.bench_function("perform_add_box_nalgebra", move |b| {
        b.iter(|| black_box(perform_add_box_nalgebra(&bm1, &bm2)))
    });
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);

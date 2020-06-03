#[macro_use]
extern crate criterion;

use criterion::{black_box, Criterion};

extern crate nalgebra as na;
use na::Matrix4;
use ndarray::{Array, ArrayView, Ix2};

use test_ndarray::*;

fn criterion_benchmark(c: &mut Criterion) {
    let m1 = Matrix4::new(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    let m2 = m1 * 2;
    let nd1 = ndarray::array![
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16]
    ];
    let nd2 = &nd1 * 2;

    c.bench_function("perform_add_nalgebra", move |b| {
        b.iter(|| black_box(perform_add_nalgebra(&m1, &m2)))
    });
    c.bench_function("perform_add_ndarray", move |b| {
        b.iter(|| black_box(perform_add_ndarray(&nd1, &nd2)))
    });

    let mut nd3 = ndarray::array![
        [1.1, 2.1, 3.1, 4.1],
        [5.1, 6.2, 7.1, 8.1],
        [9.1, 10.2, 11.3, 12.1],
        [13.1, 14.4, 15.9, 16.2]
    ];
    let nd4 = &nd3 * 1.15;
    // println!("{:?}", nd3);
    // println!("{:?}", nd4);

    c.bench_function("perform_add_ndarray_float", |b| {
        b.iter(|| black_box(perform_add_ndarray_float(&nd3, &nd4)))
    });
    c.bench_function("perform_add_mut_inplace_ndarray", |b| {
        b.iter(|| black_box(perform_add_mut_inplace_ndarray_float(&mut nd3, &nd4)))
    });
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);

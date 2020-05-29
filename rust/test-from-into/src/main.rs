use num_traits::{AsPrimitive, Float};

fn dfact6<T: Float + AsPrimitive<i128>>(n: T) -> T {
    let p: i128 = (1..(-n).as_()).step_by(2).product();
    T::from(p).unwrap()
}

fn main() {
    let n: f64 = -10.0;
    // let it = (1..n as i64).step_by(2);
    // println!("{:?}", it);
    // let p: i64 = it.product();
    // println!("{}", p);
    let p: i64 = (1..-n as i64).step_by(2).product();
    let s = p as f64;
    println!("{}", s);
    println!("{}", dfact6(n));
}

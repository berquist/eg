use num::Float;

fn add_f64_f64_to_f64(l: f64, r: f64) -> f64 {
    l + r
}

fn add_f64_i32_to_f64(l: f64, r: i32) -> f64 {
    l + r as f64
}

fn add_f64_float_to_float<T>(l: f64, r: T) -> T
where
    T: Float,
{
    T::from(l).unwrap() + r
}

fn add_float_float_to_float<T>(l: T, r: T) -> T
where
    T: Float,
{
    l + r
}

// impl From<f64> for Float {
//     fn from(n: f64) -> Self {
//         n
//     }
// }

// fn add_f64_float_to_f64<T>(l: f64, r: T) -> f64
// where
//     T: Float,
// {
//     l + f64::from(r)
// }

fn main() {
    println!("{}", add_f64_f64_to_f64(2.0, 7.0));
    println!("{}", add_f64_i32_to_f64(2.0, 7));
    println!("{}", add_f64_float_to_float(2.0, 7.0_f32));
    println!("{}", add_f64_float_to_float(2.0, 7.0_f64));
    println!("{}", add_float_float_to_float(2.0, 7.0));
    println!("{}", add_f64_float_to_float(2.0, 7.0));
}

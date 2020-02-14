use num_traits::{cast::FromPrimitive, Float, FloatConst};

fn add_point_two_five<T: Float + FromPrimitive>(z: T) -> T {
    // https://stackoverflow.com/questions/50767912/how-do-i-use-floating-point-number-literals-when-using-generic-types
    z + T::from_f64(0.25).unwrap()
}

fn add_to_pi<T: Float + FloatConst>(x: T) -> T {
    x + T::PI()
}

fn main() {
    let pi_32: f32 = FloatConst::PI();
    let pi_64: f64 = FloatConst::PI();
    println!("{}", pi_32);
    println!("{}", pi_64);
    println!("{}", add_to_pi(4.0_f32));
    println!("{}", add_to_pi(4.0_f64));
    println!("{}", add_point_two_five(2.0_f64));
    println!("{}", add_point_two_five(2.0_f32));
}

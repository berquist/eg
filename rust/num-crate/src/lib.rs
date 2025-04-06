#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(test)]
mod tests {
    use super::*;
    use num_complex::{c64, ComplexFloat};

    #[test]
    fn try_complex() {
        let c = c64(3.1, 4.2);
        let d = c64(9.9, -10.1);
        let c_bind: __BindgenComplex<f64> = __BindgenComplex { re: c.re, im: c.im };
        let d_bind: __BindgenComplex<f64> = __BindgenComplex { re: d.re, im: d.im };
        let ref_abs = unsafe { errAbs(c_bind, d_bind) };
        let ref_rel = unsafe { errRel(c_bind, d_bind) };
        println!("{:#?}", ref_abs);
        println!("{:#?}", ref_rel);
        let diff = c - d;
        println!("{:#?}", diff.abs());
        println!("{:#?}", diff.abs() / c.abs());
        // assert_eq!(ref_abs, diff.abs());
        // assert_eq!(ref_rel, diff.abs() / c.abs());
    }
}

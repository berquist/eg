#[cfg(test)]
mod tests {
    // use super::*;
    use ndarray::{arr1, arr2};

    #[test]
    fn it_works_1() {
        let a = arr1(&[1.0, 2.0, 3.0, 4.0]);
        // 1 + 4 + 9 + 16 = 1 + 4 + 25 = 30
        let ret = a.dot(&a);
        // println!("{:#?}", ret);
        assert_eq!(ret, 30.0);
    }

    #[test]
    fn it_works_2() {
        let a = arr2(&[[1., 2.], [0., 1.]]);
        let b = arr2(&[[1., 2.], [2., 3.]]);
        // println!("{:#?}", a);
        // println!("{:#?}", b);
        assert!(a.dot(&b) == arr2(&[[5., 8.], [2., 3.]]));
    }
}

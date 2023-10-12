fn main() {
    let file = hdf5::File::create("myfile.h5").expect("problem creating HDF5 file");
    println!("{:?}", file);

    let n1_ref: f64 = 1.23;
    let n2_ref: i32 = 4;
    let n3_ref: usize = 4;
    let a1 = [1.2, 3.4, 5.2];
}

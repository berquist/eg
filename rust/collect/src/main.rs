fn main() {
    let myarr = [2, 4, 5, 8, 2];
    println!("{:?}", myarr);
    let myvec: Vec<_> = myarr.iter().collect();
    println!("{:?}", myvec);
}

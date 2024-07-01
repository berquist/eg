use anyhow::Result;
use md5::{Digest, Md5};
use std::{fs, io::Cursor};
use ya_md5::Md5Hasher;

fn main() -> Result<()> {
    let s = fs::read_to_string("Cargo.toml")?;

    // https://docs.rs/yet-another-md5/2.0.0/ya_md5/
    let hash = Md5Hasher::hash(&mut Cursor::new(s.as_bytes()))?;
    println!("{}", hash);
    let hash = Md5Hasher::hash_slice(s.as_bytes());
    println!("{}", hash);
    let hash = Md5Hasher::hash_vec(&Vec::from(s.as_bytes()));
    println!("{}", hash);
    let hash = Md5Hasher::hash_str(&s);
    println!("{}", hash);

    // https://docs.rs/md5
    // println!("{}", md5::compute(s));

    // https://docs.rs/md-5/latest/md5/index.html
    let mut hasher = Md5::new();
    hasher.update(s.as_bytes());
    let result = hasher.finalize();
    let hash = format!("{:02x}", result);
    println!("{}", hash);

    Ok(())
}

use std::path::PathBuf;

const DEFAULT_IGNORES: [&str; 8] = [
    "RCS",
    "CVS",
    "tags",
    ".git",
    ".hg",
    ".bzr",
    "_darcs",
    "__pycache__",
];

fn main() {
    let myarr = [2, 4, 5, 8, 2];
    println!("{:?}", myarr);
    let myvec: Vec<_> = myarr.iter().collect();
    println!("{:?}", myvec);

    let ignores_vec: Vec<_> = DEFAULT_IGNORES.iter().map(|x| String::from(*x)).collect();
    println!("{:?}", ignores_vec);
    let ignores_vec: Vec<_> = DEFAULT_IGNORES.iter().map(|&x| String::from(x)).collect();
    println!("{:?}", ignores_vec);

    let paths_vec: Vec<_> = DEFAULT_IGNORES.iter().map(|x| PathBuf::from(*x)).collect();
    println!("{:?}", paths_vec);
    let paths_vec: Vec<_> = DEFAULT_IGNORES.iter().map(|&x| PathBuf::from(x)).collect();
    println!("{:?}", paths_vec);
}

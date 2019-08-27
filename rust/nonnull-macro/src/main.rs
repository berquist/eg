use std::ptr;

#[macro_export]
macro_rules! nonnull_unchecked_unwrap {
    ($i:ident) => {
        $i.unwrap_or_else(|| {
            if cfg!(debug_assertions) {
                unreachable!()
            } else {
                unsafe {
                    std::hint::unreachable_unchecked();
                }
            }
        })
    };
}

fn main() {
    let mut v = [9.2, 3.2];
    let a = v.as_mut_ptr();
    println!("{:#?}", v);
    println!("{:#?}", a);
    unsafe {
        *a = 1.1;
    }
    println!("{:#?}", v);
    let an = ptr::NonNull::new(a);
    println!("{:#?}", an);
    let an_unwrapped = an.unwrap();
    println!("{:#?}", an_unwrapped);
    let an2 = ptr::NonNull::new(a);
    let an2_unwrapped = an2.unwrap_or_else(|| {
        if cfg!(debug_assertions) {
            unreachable!()
        } else {
            unsafe {
                std::hint::unreachable_unchecked();
            }
        }
    });
    println!("{:#?}", an2_unwrapped);
    assert_eq!(an_unwrapped, an2_unwrapped);
    let an3 = ptr::NonNull::new(a);
    let an3_unwrapped = nonnull_unchecked_unwrap!(an3);
    println!("{:#?}", an3_unwrapped);
    assert_eq!(an_unwrapped, an3_unwrapped);
}

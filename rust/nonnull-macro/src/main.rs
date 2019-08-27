use std::ptr;

// These assume you're passing an Option<NonNull<T>>, meaning you've already
// called NonNull::new on your mutable pointer.

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

trait UncheckedUnwrap<T> {
    fn unchecked_unwrap(self) -> ptr::NonNull<T>;
}

impl<T> UncheckedUnwrap<T> for Option<ptr::NonNull<T>> {
    fn unchecked_unwrap(self) -> ptr::NonNull<T> {
        self.unwrap_or_else(|| {
            if cfg!(debug_assertions) {
                unreachable!()
            } else {
                unsafe {
                    std::hint::unreachable_unchecked();
                }
            }
        })
    }
}

// These assume you're passing a * mut T, and the NonNull needs to be
// constructed

#[macro_export]
macro_rules! create_unchecked_nonnull {
    ($i:ident) => {
        ptr::NonNull::new($i).unwrap_or_else(|| {
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

trait UncheckedNonNull<T> {
    fn to_unchecked_nonnull(self) -> ptr::NonNull<T>;
}

impl<T> UncheckedNonNull<T> for *mut T {
    fn to_unchecked_nonnull(self) -> ptr::NonNull<T> {
        ptr::NonNull::new(self).unwrap_or_else(|| {
            if cfg!(debug_assertions) {
                unreachable!()
            } else {
                unsafe {
                    std::hint::unreachable_unchecked();
                }
            }
        })
    }
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

    let an4 = ptr::NonNull::new(a);
    let an4_unwrapped = an4.unchecked_unwrap();
    println!("{:#?}", an4_unwrapped);
    assert_eq!(an_unwrapped, an4_unwrapped);

    let an5 = a.clone();
    let an5_unwrapped = an5.to_unchecked_nonnull();
    println!("{:#?}", an5_unwrapped);
    assert_eq!(an_unwrapped, an5_unwrapped);

    let an6 = a.clone();
    let an6_unwrapped = create_unchecked_nonnull!(an6);
    println!("{:#?}", an6_unwrapped);
    assert_eq!(an_unwrapped, an6_unwrapped);
}

#[cxx::bridge]
mod ffi {
    extern "C++" {
        include!("test-cxx/include/wrapper.hpp");
        type Dummy;
        fn make_new_dummy() -> UniquePtr<Dummy>;
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}

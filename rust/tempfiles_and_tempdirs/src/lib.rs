#[cfg(test)]
mod tests {
    use tempfile;

    #[test]
    fn create_tempfile_bare() {
        let _tf = dbg!(tempfile::tempfile().unwrap());
    }

    #[test]
    fn create_tempdir_bare() {
        let _td = dbg!(tempfile::tempdir().unwrap());
    }

    #[test]
    fn create_tempdir_with_tempfile() {
        let td = dbg!(tempfile::tempdir().unwrap());
        let _tf = dbg!(tempfile::tempfile_in(td).unwrap());
    }
}

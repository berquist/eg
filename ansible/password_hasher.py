import argparse

from passlib.hash import sha256_crypt

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("password")
    args = parser.parse_args()
    print(sha256_crypt.hash(args.password))

from setuptools import setup, Extension
from Cython.Build import cythonize

setup(
    ext_modules=cythonize(
        [
            Extension(
                "*",
                ["using_cython.pyx"],
                include_dirs=["include"],
                library_dirs=["build"],
                libraries=["mylib"],
            )
        ]
    )
)

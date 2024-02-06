from Cython.Build import cythonize
from setuptools import Extension, setup

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

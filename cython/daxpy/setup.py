from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy

setup(
    ext_modules=cythonize(
        [
            Extension(
                "*",
                ["using_cython.pyx"],
                include_dirs=[".", numpy.get_include()],
                library_dirs=["build"],
                libraries=["mylib"],
            )
        ]
    )
)

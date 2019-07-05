## f2py

## Cython

See https://github.com/HolgerPeters/cython-example for multiple examples of how to do linking. The current approach here requires

``` shell
LD_LIBRARY_PATH="build:$LD_LIBRARY_PATH" python using_cython_example.py
```

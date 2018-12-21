"""
Naive dotproduct! Pythran supports numpy.dot
"""
#pythran export dprod(float list or float [], float list or float [])
def dprod(l0, l1):
    """WoW, generator expression, zip and sum."""
    return sum(x * y for x, y in zip(l0, l1))

# now run `$ pythran test_pythran.py`

# from pprint import pprint

import numpy as np
import numpy.linalg as npl
import scipy.linalg as spl

if __name__ == "__main__":
    mat = np.array(
        [
            [-0.386087, 0.00813956, 0.0781361],
            [0.00813956, -0.390147, 0.0986476],
            [0.0781361, 0.0986476, 0.776234],
        ]
    )

    print(mat)
    # pprint(dir(np))
    eval_np, evec_np = npl.eigh(mat)
    print(eval_np)
    print(evec_np)
    eval_sp, evec_sp = spl.eigh(mat)
    # print(eval_sp)
    # print(evec_sp)
    # pprint(dir(np.testing))
    assert np.allclose(eval_np, eval_sp)
    assert np.allclose(evec_np, evec_sp)

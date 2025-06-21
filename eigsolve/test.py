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
    idx = eval_np.argsort()
    print(eval_np[idx])
    print(evec_np[:, idx])
    eval_sp, evec_sp = spl.eigh(mat)
    # print(eval_sp[idx])
    # print(evec_sp[:, idx])
    # pprint(dir(np.testing))
    assert np.allclose(eval_np[idx], eval_sp[idx])
    assert np.allclose(evec_np[:, idx], evec_sp[:, idx])

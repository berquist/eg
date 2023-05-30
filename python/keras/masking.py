from pprint import pprint

import numpy as np
from keras.layers import Dense, Input, Masking, TimeDistributed
from keras.models import Model

if __name__ == "__main__":
    inp = Input(shape=(3, 6))
    mask = Masking(mask_value=0.1)(inp)
    out = TimeDistributed(Dense(1, activation="linear"))(mask)
    model = Model(inputs=inp, outputs=out)

    print("Architecture")
    model.summary()

    model.set_weights(
        [
            np.array([[1.0], [1.0], [1.0], [1.0], [1.0], [1.0]], dtype=np.float32),
            np.array([0.0], dtype=np.float32),
        ]
    )

    print("Weights")
    pprint(model.get_weights())

    data = np.array(
        [[[3, 1, 2, 2, 0.1, 0.1], [0, 0, 0, 0, 0, 0], [2, 1, 1, 2, 0.1, 0.1]]]
    )
    p = model.predict(data)
    print(p)

    # Masking only works when all features of a timestep are equal to the mask
    # value.
    #
    # From https://github.com/keras-team/keras/issues/3086#issuecomment-526057828
    data = np.array(
        [[[3, 1, 2, 2, 0.1, 0.1], [0, 0, 0, 0, 0, 0], [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]]]
    )
    p = model.predict(data)
    print(p)

from attr import attrib, attrs
from attr.validators import instance_of

import pytest


@attrs(slots=True, frozen=True)
class A:
    first: str = attrib(validator=instance_of(str))

    @first.validator
    def _validate_first(self, _, val) -> None:
        if val != "first":
            raise ValueError(f"val is {val} and not 'first'")


def test_validation() -> None:
    a1 = A("first")
    with pytest.raises(ValueError, match="val is second and not 'first'") as excinfo:
        a2 = A("second")
    with pytest.raises(TypeError, match=r"must be <class 'str'>") as excinfo:
        a3 = A(True)

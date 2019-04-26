from __future__ import print_function
import pytest
import six
import sys
from abc import ABCMeta, abstractmethod
from inspect import isabstract


class Foo(object):
    pass


class Abstract:
    __metaclass__ = ABCMeta

    @abstractmethod
    def foo(self):
        pass


@six.add_metaclass(ABCMeta)
class AbstractSix:
    @abstractmethod
    def foo(self):
        pass


@pytest.mark.skipif(
    sys.version_info > (2, 7), reason="__metaclass__ is not read for Python 3.x"
)
def test_isabstract():
    assert not isabstract(Foo)
    assert isabstract(Abstract)
    assert isabstract(AbstractSix)

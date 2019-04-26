import six
from abc import ABC, ABCMeta, abstractmethod
from inspect import isabstract


class Foo(object):
    pass


# Python 3.4+
class Abstract34(ABC):
    @abstractmethod
    def foo(self):
        pass


# Python 3.0+
class Abstract30(metaclass=ABCMeta):
    @abstractmethod
    def foo(self):
        pass


# Python 2
class Abstract2:
    __metaclass__ = ABCMeta

    @abstractmethod
    def foo(self):
        pass


@six.add_metaclass(ABCMeta)
class AbstractSix:
    @abstractmethod
    def foo(self):
        pass


def test_isabstract():
    assert not isabstract(Foo)
    assert isabstract(Abstract34)
    assert isabstract(Abstract30)
    assert not isabstract(Abstract2)
    assert isabstract(AbstractSix)

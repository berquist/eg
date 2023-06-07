from typing import Callable

import pytest

# def skip_for_parser(parser: str, msg: str):
#     """Return a decorator that skips the test for specified parser."""

#     def testdecorator(testfunc: Callable) -> Callable[[], None]:
#         def testwrapper(self, *args, **kwargs) -> None:
#             if self.logfile.logname == parser:
#                 self.skipTest(msg)
#             else:
#                 testfunc(self, *args, **kwargs)

#         return testwrapper

#     return testdecorator


# def skip_for_logfile(fragment: str, msg: str):
#     """Return a decorator that skips the test for logfiles containing fragment.
#     """

#     def testdecorator(testfunc: Callable) -> Callable[[], None]:
#         def testwrapper(self, *args, **kwargs) -> None:
#             # self.logfile.filename may be a string or list of strings.
#             if fragment in self.logfile.filename or any(
#                 fragment in filename for filename in self.logfile.filename
#             ):
#                 self.skipTest(msg)
#             else:
#                 testfunc(self, *args, **kwargs)

#         return testwrapper

#     return testdecorator


def test_normal() -> None:
    """This is my normal test."""
    print("This is my normal test.")


def nothing(_: Callable[[], None]) -> Callable[[], None]:
    """A test decorator that doesn't do anything.

    The TODO is called at test collection time.
    """
    # def testdecorator(testfunc):
    #     def testwrapper(self, *args, **kwargs):
    #         testfunc(self, *args, **kwargs)
    #     return testwrapper
    print("Inside nothing before testdecorator definition")

    def testdecorator() -> None:
        print("Inside testdecorator")
        # /usr/lib/python3.11/site-packages/_pytest/python.py:198:
        # PytestReturnNotNoneWarning: Expected None, but
        # pytest_decorators.py::test_decorated_nothing returned <function
        # test_decorated_nothing at 0x7f07ec540c20>, which will be an error in
        # a future version of pytest.  Did you mean to use `assert` instead of
        # `return`?
        #
        # return fragment

    print("Inside nothing after testdecorator definition")
    return testdecorator


def skip_on_function_name(testfunc: Callable[[], None]) -> Callable[[], None]:
    """A decorator that skips a test when its name contains 'skip_2'."""
    print("@before")

    def testdecorator() -> None:
        print("@inside")
        if "skip_2" in testfunc.__name__:
            print("@skipped")
            pytest.skip(reason="matched!")

    print("@after")
    return testdecorator


def skip_on_function_name2(name: str) -> Callable[[Callable[[], None]], Callable[[], None]]:
    """A decorator that skips a test when its name contains 'name'."""

    def testdecorator(testfunc: Callable[[], None]) -> Callable[[], None]:
        def testwrapper() -> None:
            if name in testfunc.__name__:
                pytest.skip(reason=f"matched '{name}'!")

        return testwrapper

    return testdecorator


@nothing
def test_decorated_nothing() -> None:
    """This is a test that's decorated but the decorator does nothing."""
    print("This is a test that's decorated but the decorator does nothing.")


@skip_on_function_name
def test_decorated_skip_1() -> None:
    """test_decorated_skip_1 won't match"""


@skip_on_function_name
def test_decorated_skip_2() -> None:
    """test_decorated_skip_1 will match"""


@skip_on_function_name2("yes")
def test_no() -> None:
    pass


@skip_on_function_name2("yes")
def test_yes() -> None:
    pass

from typing import Callable

import pytest


def skipForParser(parser, msg: str):
    """Return a decorator that skips the test for specified parser."""

    def testdecorator(testfunc):
        def testwrapper(self, *args, **kwargs):
            if self.logfile.logname == parser:
                self.skipTest(msg)
            else:
                testfunc(self, *args, **kwargs)

        return testwrapper

    return testdecorator


def skipForLogfile(fragment, msg: str):
    """Return a decorator that skips the test for logfiles containing fragment."""

    def testdecorator(testfunc):
        def testwrapper(self, *args, **kwargs):
            # self.logfile.filename may be a string or list of strings.
            if fragment in self.logfile.filename or any(
                fragment in filename for filename in self.logfile.filename
            ):
                self.skipTest(msg)
            else:
                testfunc(self, *args, **kwargs)

        return testwrapper

    return testdecorator


def test_normal() -> None:
    """This is my normal test."""
    print("This is my normal test.")


def nothing(fragment):
    """A test decorator that doesn't do anything.

    The TODO is called at test collection time.
    """
    # def testdecorator(testfunc):
    #     def testwrapper(self, *args, **kwargs):
    #         testfunc(self, *args, **kwargs)
    #     return testwrapper
    print("Inside nothing before testdecorator definition")

    def testdecorator():
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


def skip_on_function_name(fragment: Callable):
    print("@before")

    def testdecorator():
        print("@inside")
        if "skip_2" in fragment.__name__:
            # breakpoint()
            print("@skipped")
            pytest.skip(reason="matched!")

    print("@after")
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

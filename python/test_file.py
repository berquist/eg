import os.path
from pathlib import Path

__dir1__ = str(Path(__file__).resolve().parent)
__dir2__ = os.path.dirname(os.path.abspath(__file__))

# print(__dir1__)
# print(__dir2__)
assert __dir1__ == __dir2__

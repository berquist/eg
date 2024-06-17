import subprocess as sp
from argparse import ArgumentParser
from pathlib import Path

parser = ArgumentParser()
parser.add_argument("fn", type=Path)
args = parser.parse_args()
fn = args.fn

lines = ""
for line in fn.read_text(encoding="utf-8").splitlines():
    line = line.strip()
    if not line.startswith("#"):
        # f"--build-arg=\"{line}\""
        # To mimic bash implementation rather than append to list then join on string
        lines = f"{lines} --build-arg={line}"
print(lines)
sp.run(f"podman build --no-cache {lines} -t myimage .", shell=True)

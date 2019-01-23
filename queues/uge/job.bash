#!/usr/bin/env bash

# source ~/.bashrc

# Thanks, /etc/bashrc!
set -euxo pipefail

# export PATH=${apps}/python/miniconda3/bin:${PATH}
export PATH=${HOME}/opt/apps/python/miniconda3/bin:${PATH}

env | sort

$(command -v python) sample.py

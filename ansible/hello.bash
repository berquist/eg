#!/usr/bin/env bash

# https://www.ansibletutorials.com/hello-ansible

ansible all \
        --inventory "localhost," \
        --module-name debug \
        --args "msg='Hello Ansible'"

# a shorter version:

ansible all \
        -i "localhost," \
        -m debug \
        -a "msg='Hello Ansible'"

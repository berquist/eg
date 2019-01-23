#!/usr/bin/env sh

# G, not GB!
qsub -P other -N "uge_example" -cwd -l h_vmem=4G,h_rt=00:30:00 job.bash

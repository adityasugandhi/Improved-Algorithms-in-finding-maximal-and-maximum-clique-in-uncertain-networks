#!/bin/bash

ulimit -v 16000000  # Set the hard limit to 16 GB in kilobytes

../uclique /home/csgroup/Uclique/data/askubuntu 6 0.01 5 1

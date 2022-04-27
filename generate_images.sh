#!/bin/bash

ls *.png | xargs -I{} ./png2bin.py {}

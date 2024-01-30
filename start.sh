#!/bin/bash
# This is a comment

cd /opt/c2
make clean
make
cd cpp
make clean
make
sudo ./mycpp ../LCD_1inch28_1.bmp
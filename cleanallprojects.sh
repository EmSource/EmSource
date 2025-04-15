#!/bin/bash

find . -name "*_linux64_hl2.mak" -exec rm {} \;
find . -name "*_linux64.mak" -exec rm {} \;
find . -name "*_linux32_hl2.mak" -exec rm {} \;
find . -name "*_linux32.mak" -exec rm {} \;

if [ -f "Makefile" ]; then
    rm "Makefile"
fi

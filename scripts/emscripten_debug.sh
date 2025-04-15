cd ../src
export NO_VALVE_AUTO_P4
devtools/bin/vpc_emscripten /hl2 +everything /mksln Makefile
mv Makefile.mak Makefile
EMCC_DEBUG=1 emmake make #Makefile

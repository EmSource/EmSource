#!/bin/bash
set -e

./../devtools/vpc_emscripten /hl2 +everything ../Makefile
mv Makefile.mak Makefile
GAME="hl2"
BIN_DIR="../../game/bin"
GAME_BIN_DIR="../../$GAME/bin"
emmake make -f "..//Makefile"
cd "$BIN_DIR"
emcc engine.so "$GAME_BIN_DIR"/*.so -O2 -s WASM=1 -o hl2.html

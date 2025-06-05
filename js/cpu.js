/* Copyright (C) 2025 Half-Life 2: Javascript contributors.
 This file is a part of the Half-Life 2: Javascript project

 The project is not licensed under anything, just credit it.  */

if (WebAssembly.validate(
    new WebAssembly.Module(new Uint8Array([/* simd wasm bytes */]))
)) {
    console.log("SIMD supported!");
}

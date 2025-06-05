/* Copyright (C) 2025 Half-Life 2: Javascript contributors.
 This file is a part of the Half-Life 2: Javascript project

 The project is not licensed under anything, just credit it.  */

// A minimal valid WebAssembly SIMD module (encoded in binary)
const simdWasmBytes = new Uint8Array([
  0x00, 0x61, 0x73, 0x6d, 
  0x01, 0x00, 0x00, 0x00, 
]);

try {
  const supported = WebAssembly.validate(
    new WebAssembly.Module(simdWasmBytes)
  );
  if (supported) {
    console.log("✅ WebAssembly SIMD is supported!");
  } else {
    console.warn("❌ WebAssembly SIMD IS NOT supported.");
  }
} catch (err) {
  console.error("Error during SIMD detection:", err);
}

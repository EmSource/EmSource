#ifdef __wasm64__
#define PTR i64
#else
#define PTR i32
#endif

.globl _emscripten_memcpy_bulkmem
_emscripten_memcpy_bulkmem:
  .functype _emscripten_memcpy_bulkmem (PTR, PTR, PTR) -> (PTR)
  local.get 2
#ifdef __wasm64__
  i32.wrap_i64
#endif
  // memory.copy traps on OOB zero-length copies, but memcpy must not.
  if
    local.get 0
    local.get 1
    local.get 2
    memory.copy 0, 0
  end_if
  local.get 0
  end_function

.section .custom_section.target_features,"",@
.int8 1
.int8 43
.int8 11
.ascii "bulk-memory"

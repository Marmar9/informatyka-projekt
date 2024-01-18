(module
  (type (;0;) (func (param i32)))
  (type (;1;) (func))
  (type (;2;) (func (result i32)))
  (type (;3;) (func (param i32 i32) (result i32)))
  (type (;4;) (func (param i32) (result i32)))
  (import "wasi_snapshot_preview1" "proc_exit" (func (;0;) (type 0)))
  (func (;1;) (type 1))
  (func (;2;) (type 3) (param i32 i32) (result i32)
    i32.const 25)
  (func (;3;) (type 1)
    i32.const 25
    call 0
    unreachable)
  (func (;4;) (type 2) (result i32)
    i32.const 1024)
  (func (;5;) (type 2) (result i32)
    global.get 0)
  (func (;6;) (type 0) (param i32)
    local.get 0
    global.set 0)
  (func (;7;) (type 4) (param i32) (result i32)
    global.get 0
    local.get 0
    i32.sub
    i32.const -16
    i32.and
    local.tee 0
    global.set 0
    local.get 0)
  (table (;0;) 2 2 funcref)
  (memory (;0;) 256 256)
  (global (;0;) (mut i32) (i32.const 66576))
  (export "memory" (memory 0))
  (export "main" (func 2))
  (export "__indirect_function_table" (table 0))
  (export "_start" (func 3))
  (export "__errno_location" (func 4))
  (export "stackSave" (func 5))
  (export "stackRestore" (func 6))
  (export "stackAlloc" (func 7))
  (elem (;0;) (i32.const 1) func 1))

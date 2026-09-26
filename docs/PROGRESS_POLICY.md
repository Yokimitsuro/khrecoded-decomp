# Progress policy

Progress is split into categories so contributors and external trackers can see
what has actually been decompiled into C.

## Real C decompilation

A function counts as real C decompilation only when it is implemented in C and
passes byte-exact verification against the original code
(`tools/verify_idx.py`), and the full build still links every module
byte-identical to the ROM (`tools/gate.sh`).

Functions ported from khdays-decomp (see [PORTING_FROM_DAYS.md](PORTING_FROM_DAYS.md))
are held to exactly the same standard: they are real C that recompiles to this
ROM's bytes, and each one is verified here, not assumed from the other project.

## Library assembly

Some library functions were written in assembly by their authors: NitroSDK's
`asm` functions (cache and protection-unit control, interrupt masking, context
switches, copy/fill kernels, matrix helpers), the BIOS SWI veneers and the
CodeWarrior runtime helpers. Many use instructions C cannot express with this
compiler (`mcr`/`mrc`, `mrs`/`msr`, `swi`). They live under
`libs/**/asm_stubs/` as that original assembly, verify byte-exact and are shown
separately. They never count as C.

## ASM stubs

Inline ASM or placeholder assembly for game code may be used temporarily while
researching a function. It may match the original bytes, but it does not count
as C-decompiled progress and belongs under `asm_stubs/`.

## Named functions

A function may have a known name (for example a NitroSDK name carried over from
khdays-decomp where the evidence is one-to-one) before it has a C
implementation. Names help research, but they do not count as progress.

## Why this matters

Byte-exact matching is the technical verification gate, but public progress
only counts real C implementations, measured both by function count and, more
honestly, by code bytes.

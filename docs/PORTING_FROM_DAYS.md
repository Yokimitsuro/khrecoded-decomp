# Porting functions from khdays-decomp

*Kingdom Hearts Re:coded* and *Kingdom Hearts 358/2 Days* were built with the
same CodeWarrior toolchain and share a large amount of code: the NitroSDK and
NitroSystem libraries, the Metrowerks standard library, the MobiClip movie
middleware and parts of the engine. Wherever a function is identical in both
ROMs, the byte-exact C of
[khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp) can be reused.

`tools/port_days.py` does this mechanically and conservatively.

## What it does

1. **Find candidates.** Both projects index every function (bytes, relocation
   offsets, ARM/THUMB mode). Two functions are candidates when their bytes are
   identical once the relocated words are masked, and their relocations sit at
   the same offsets. With `--scan`, every Days source is also compiled in the
   *other* instruction set, because Re:coded builds most of its game code as
   THUMB where Days used ARM.
2. **Compile the donor.** The Days source is compiled in this function's mode
   with the project flags, and its bytes and relocation offsets must again equal
   this ROM's. Sources that define anything besides the function itself (static
   helpers, string literals, tables) are skipped, since this tree would have to
   lay that data down as well.
3. **Remap symbols.** Every relocation of the compiled object names a symbol
   and an addend. The relocation at the same site in this ROM gives the real
   target address; the symbol at `target - addend` in the target module is the
   new name. A mapping must be one-to-one: if one Days symbol would become two
   different symbols here (or two become one), the function is not the same
   code and is skipped.
4. **Rewrite and verify.** The source is rewritten with the new names (game
   code loses its Days comments, which describe the other game; library code
   keeps them) and verified with `tools/verify_idx.py`. Anything that does not
   report `>>> MATCH <<<` is deleted.

With `--names`, names are carried over as well, but only for this project's
placeholder symbols (`func_XXXXXXXX`, `data_XXXXXXXX`), only from functions
that are identical as indexed (not from a cross-mode recompile) and at least 8
bytes long, only for library/engine names (never Days overlay-specific or
address-bearing names), and only when the evidence is one-to-one in both
directions.

With `--asm`, the original library assembly that khdays-decomp integrated
(NitroSDK `asm` functions, BIOS veneers, runtime helpers) is ported too, into
`asm_stubs/` directories; it never counts as C.

## Usage

```sh
# in the khdays-decomp checkout: produce its function index once
python tools/rebuild_index.py --write

# here
python tools/rebuild_index.py --write
python tools/port_days.py --days <path-to-khdays-decomp> --scan --names --asm        # dry run
python tools/port_days.py --days <path-to-khdays-decomp> --scan --names --asm --write
bash tools/gate.sh
```

The tool never overwrites an existing source, so it can be re-run whenever
khdays-decomp matches more functions.

## Limits

Only exact code matches are handled. Functions that differ between the games
by a constant, a structure offset or an extra call (for example because of a
newer NitroSDK release) need to be decompiled by hand, although the Days C is
often a good starting point.

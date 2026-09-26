<!-- Thanks for contributing! Keep PRs focused (one module or a few functions). -->

## What this PR decompiles

<!-- List the functions you matched, or the module (e.g. ov001). -->

## Checklist

- [ ] Every function verifies byte-exact (`>>> MATCH <<<` from `tools/verify_idx.py`)
- [ ] `bash tools/gate.sh` passes (all modules byte-exact)
- [ ] `PROGRESS.md` / `README.md` regenerated (`tools/progress.py`, `tools/update_readme.py`)
- [ ] Only source and config changes: **no** ROM, assets, compiler, or binaries

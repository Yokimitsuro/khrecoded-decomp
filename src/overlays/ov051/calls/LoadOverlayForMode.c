extern int func_ov051_020c72e0(unsigned int selectionIndex);
extern int func_ov051_020c72f8(unsigned int selectionIndex);
extern int func_ov051_020c7378(unsigned int selectionIndex);
extern int func_ov051_020c7310(unsigned int selectionIndex);
int LoadOverlayForMode(unsigned int selectionIndex, int mode)
{
    switch ((unsigned int)mode + 1U) {
    case 0: return func_ov051_020c7378(selectionIndex);
    case 2: return func_ov051_020c72f8(selectionIndex);
    case 3: return func_ov051_020c7310(selectionIndex);
    case 1:
    default: return func_ov051_020c72e0(selectionIndex);
    }
}

extern const unsigned char *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void func_02029f8c(int processor, int overlayId);
extern int data_ov051_020c7420[][3];
extern void (*data_ov051_020c73f0[][3])(void);
extern int data_ov051_020c7460[3];
int LoadNextOverlayForSelection(unsigned int selectionIndex)
{
    int selection = *GetOverlaySelectionRecord(selectionIndex);
    int overlayId;
    int slot;
    for (slot = 2; slot >= 0; --slot) {
        if (data_ov051_020c7460[slot] == -1 && data_ov051_020c7420[selection][slot] != -1 && data_ov051_020c73f0[selection][slot]) {
            overlayId = data_ov051_020c7420[selection][slot];
            data_ov051_020c7460[slot] = overlayId;
            break;
        }
    }
    func_02029f8c(0, overlayId);
    if (data_ov051_020c73f0[selection][slot]) {
        data_ov051_020c73f0[selection][slot]();
    }
    return overlayId;
}

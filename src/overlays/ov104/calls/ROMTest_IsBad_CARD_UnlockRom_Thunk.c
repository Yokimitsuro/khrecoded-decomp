extern void *CARD_UnlockRom();

void *ROMTest_IsBad_CARD_UnlockRom_Thunk() {
    return CARD_UnlockRom();
}

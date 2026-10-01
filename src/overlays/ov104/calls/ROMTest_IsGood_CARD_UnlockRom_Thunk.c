extern void *CARD_UnlockRom();

void *ROMTest_IsGood_CARD_UnlockRom_Thunk() {
    return CARD_UnlockRom();
}

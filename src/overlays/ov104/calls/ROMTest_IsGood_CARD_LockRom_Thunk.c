extern void *CARD_LockRom();

void *ROMTest_IsGood_CARD_LockRom_Thunk() {
    return CARD_LockRom();
}

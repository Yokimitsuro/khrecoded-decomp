extern void *CARD_LockRom();

void *ROMTest_IsBad_CARD_LockRom_Thunk() {
    return CARD_LockRom();
}

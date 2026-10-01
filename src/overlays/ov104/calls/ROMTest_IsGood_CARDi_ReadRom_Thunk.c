extern void *CARDi_ReadRom();

void *ROMTest_IsGood_CARDi_ReadRom_Thunk() {
    return CARDi_ReadRom();
}

extern void *CARDi_ReadRom();

void *ROMTest_IsBad_CARDi_ReadRom_Thunk() {
    return CARDi_ReadRom();
}

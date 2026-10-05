extern void *CARD_TryWaitBackupAsync();

void *PXI_Init_02026ca8() {
    return CARD_TryWaitBackupAsync();
}

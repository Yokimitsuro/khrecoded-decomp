extern int sCellTransferStateManager;

int NNSi_G2dGetCellTransferState(int arg0) {
    return *(int *)((char *)&sCellTransferStateManager + 8) + arg0 * 0x30;
}

extern void OS_UnLockCartridge();
extern void OS_RestoreInterrupts(int state);

void CTRDGi_UnlockByProcessor(int id, int *ctx) {
    if (ctx[0] == 0) {
        OS_UnLockCartridge(id);
    }
    OS_RestoreInterrupts(ctx[1]);
}

extern int CARD_TryWaitBackupAsync(void);
extern void CARD_WaitBackupAsync(void);
extern void func_0200923c(int resource, int kind);

void func_020091cc(int resource) {
    if (CARD_TryWaitBackupAsync() == 0)
        CARD_WaitBackupAsync();
    func_0200923c(resource, 2);
}

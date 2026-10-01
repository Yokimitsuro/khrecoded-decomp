extern int CARD_IsEnabled(void);
extern void OS_Terminate(void);

void CARD_CheckEnabled(void) {
    if (CARD_IsEnabled() == 0) {
        OS_Terminate();
    }
}

extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int interrupt_state);
extern int *data_02057c50[];

int *PopSoundCommand(void) {
    int interrupt_state;
    int *free_node;
    int *next_free_node;
    interrupt_state = OS_DisableInterrupts();
    free_node = data_02057c50[0];
    if (free_node == 0) {
        OS_RestoreInterrupts(interrupt_state);
        return 0;
    }
    next_free_node = (int *)*free_node;
    data_02057c50[0] = next_free_node;
    if (next_free_node == 0) data_02057c50[4] = 0;
    OS_RestoreInterrupts(interrupt_state);
    return free_node;
}

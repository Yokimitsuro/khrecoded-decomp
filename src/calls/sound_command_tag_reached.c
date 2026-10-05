extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int interruptState);
extern unsigned int data_02057c50[];

int sound_command_tag_reached(unsigned int requestedTag) {
    int interruptState;
    int isReached;
    unsigned int currentTag;
    interruptState = OS_DisableInterrupts();
    currentTag = data_02057c50[1];
    if (requestedTag > currentTag) {
        if ((requestedTag - currentTag) < 0x80000000u) {
            isReached = 0;
        } else {
            isReached = 1;
        }
    } else {
        if ((currentTag - requestedTag) < 0x80000000u) {
            isReached = 1;
        } else {
            isReached = 0;
        }
    }
    OS_RestoreInterrupts(interruptState);
    return isReached;
}

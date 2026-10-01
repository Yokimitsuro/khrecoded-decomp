/* Reports whether the reset request has arrived from the ARM7. */

extern unsigned short OSi_IsResetOccurred;

int OS_IsResetOccurred(void) {
    return OSi_IsResetOccurred;
}

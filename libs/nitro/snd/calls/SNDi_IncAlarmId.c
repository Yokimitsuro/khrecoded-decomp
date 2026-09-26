/* SNDi_IncAlarmId: bumps the id byte (+8) of alarm slot `n` (stride 0xc). */

extern unsigned char data_02059720;

void SNDi_IncAlarmId(int n) {
    ++*(unsigned char *)((int)&data_02059720 + n * 0xc + 8);
}

extern void SND_SetChannelVolume(int ch, int vol, int flags);
extern void SND_FlushCommand(int);
void func_ov022_020a7db4(void) {
    SND_SetChannelVolume(3, 0x7f, 0);
    SND_FlushCommand(1);
}

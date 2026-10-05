extern void SND_SetChannelVolume(int ch, int unknown_argument_a, int unknown_argument_b);
extern unsigned int SND_GetCurrentCommandTag(void);
extern void SND_FlushCommand(int unknown_argument_a);
extern void SND_WaitForCommandProc(unsigned int sound_command_tag);
extern void SND_StopTimer(int ch, int unknown_argument_a, int unknown_argument_b, int unknown_argument_c);
extern void SND_UnlockChannel(int ch, int unknown_argument_a);

void StopMovieAudio(void) {
    unsigned int sound_command_tag;

    SND_SetChannelVolume(3, 0, 0);
    sound_command_tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(sound_command_tag);
    SND_StopTimer(3, 0, 0, 0);
    SND_UnlockChannel(3, 0);
    SND_FlushCommand(1);
}

extern void NNS_SndPlayerPauseByPlayerNo(int a, int b);

void SNDi_BroadcastChannelOp(int arg0)
{
    int i;
    for (i = 2; i < 0x20; i++) {
        NNS_SndPlayerPauseByPlayerNo(i, arg0);
    }
}

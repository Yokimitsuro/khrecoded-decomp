extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void SND_SetupChannelPcm(int nChannel, int nFormat, const void *pData,
                          int nLoop, int nLoopStart, int nLoopLength,
                          int nVolume, int nShift, int nTimer, int nPan)
{
    int startFmtLoopPan = nLoopStart | (((nLoop << 26) | (nFormat << 24)) | (nPan << 16));
    int lenVolShift = nLoopLength | ((nVolume << 24) | (nShift << 22));
    int chanTimer = nChannel | (nTimer << 16);
    PushCommand_impl(0xe, chanTimer, (int)pData, lenVolShift, startFmtLoopPan);
}

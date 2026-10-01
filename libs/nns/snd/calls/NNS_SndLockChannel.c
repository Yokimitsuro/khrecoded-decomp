typedef struct NNSSndResourceLocks {
    unsigned int alarm;
    unsigned int capture;
    unsigned int channel;
} NNSSndResourceLocks;

extern NNSSndResourceLocks data_0205d894;
extern void SND_LockChannel(unsigned int channelMask, unsigned int flags);

int NNS_SndLockChannel(unsigned int channelMask)
{
    if (channelMask == 0) {
        return 1;
    }
    if ((channelMask & data_0205d894.channel) != 0) {
        return 0;
    }
    SND_LockChannel(channelMask, 0);
    data_0205d894.channel |= channelMask;
    return 1;
}

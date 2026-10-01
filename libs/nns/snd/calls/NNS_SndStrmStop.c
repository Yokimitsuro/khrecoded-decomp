typedef struct NNSSndStrm {
    unsigned char padding00[0x2c];
    signed int active : 1;
} NNSSndStrm;

extern void ForceStopStrm(NNSSndStrm *stream);

void NNS_SndStrmStop(NNSSndStrm *stream)
{
    if (!stream->active) {
        return;
    }

    ForceStopStrm(stream);
}

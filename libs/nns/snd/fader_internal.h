#ifndef NNS_SND_FADER_INTERNAL_H
#define NNS_SND_FADER_INTERNAL_H

typedef long long s64;
typedef int BOOL;

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

void NNSi_SndFaderInit(NNSSndFader *fader);
void NNSi_SndFaderSet(NNSSndFader *fader, int target, int frame);
int NNSi_SndFaderGet(const NNSSndFader *fader);
void NNSi_SndFaderUpdate(NNSSndFader *fader);
BOOL NNSi_SndFaderIsFinished(const NNSSndFader *fader);

#endif
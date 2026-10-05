#include "nitro/types.h"

typedef struct SeqRequest {
    int seqArcNo;
    int seqIndex;
    int fadeFrames;
    int pendingAction;
} SeqRequest;

typedef struct SeqRequestOwner {
    u8 pad_00[0x10];
    SeqRequest requests[2];
} SeqRequestOwner;

extern void PlaySoundChecked(int seqArcNo, int seqIndex);
extern void StopSeqArcOrDefault(int seqArcNo, int seqIndex, int fadeFrames);

void ApplyPendingSeqRequests(SeqRequestOwner *owner)
{
    int requestIndex;

    for (requestIndex = 0; requestIndex < 2; requestIndex++) {
        switch (owner->requests[requestIndex].pendingAction) {
        case 1:
            PlaySoundChecked(owner->requests[requestIndex].seqArcNo, owner->requests[requestIndex].seqIndex);
            break;
        case 2:
            StopSeqArcOrDefault(owner->requests[requestIndex].seqArcNo, owner->requests[requestIndex].seqIndex, owner->requests[requestIndex].fadeFrames);
            break;
        }
        owner->requests[requestIndex].pendingAction = 0;
    }
}

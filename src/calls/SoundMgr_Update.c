#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct SoundSlot {
    struct SoundSlot *next;
    u8 pad_04[0x12];
    s16 playerNo;
} SoundSlot;

typedef struct {
    u8 pad_00000[0xb44d8];
    NNSSndHandle bgmHandle;
    u8 pad_b44dc[0xb471c - 0xb44dc];
    SoundSlot *activeSlots;
    u8 pad_b4720[0xb472a - 0xb4720];
    s16 currentBgmId;
    s16 pendingBgmId;
    u8 phase;
    u8 bgmVolume;
    int fadeTimer;
    s16 savedSeqVar;
    s16 savedBgmId;
    u8 pad_b4738[0xb47be - 0xb4738];
    u8 command;
    u8 commandSoundId;
    u16 commandFadeFrames;
    u8 pad_b47c2[0xb47d3 - 0xb47c2];
    u8 commandReady;
} SoundWork;

extern SoundWork *data_0206084c;
extern const u8 data_020559ec[];
extern void func_0204caf8(void);
extern void PopQueuedSound(void);
extern int GetRecentHistoryEntry(int value);
extern void PauseBgmForState(u16 fadeFrames);
extern void FreeSoundHandleSlot(SoundSlot *slot);
extern void UpdateSoundSlotSpatial(SoundSlot *slot);
extern void RequestSoundLoad(u32 soundId);
extern void NNS_SndPlayerStopSeq(NNSSndHandle *handle, BOOL flag);
extern int NNS_SndPlayerCountPlayingSeqByPlayerNo(int playerNo);
extern void NNS_SndPlayerMoveVolume(NNSSndHandle *handle, int targetVolume, int frames);
extern BOOL NNS_SndPlayerReadVariable(NNSSndHandle *handle, int varNo, s16 *var);
extern BOOL NNS_SndPlayerWriteVariable(NNSSndHandle *handle, int varNo, s16 var);
extern BOOL NNS_SndArcPlayerStartSeq(NNSSndHandle *handle, int seqNo);
extern void NNS_SndMain(void);

void SoundMgr_Update(void)
{
    SoundWork *work = data_0206084c;

    func_0204caf8();

    switch (work->phase) {
    case 0:
        if (work->commandReady != 0) {
            PopQueuedSound();
            switch (work->command) {
            case 1:
            case 2:
            case 4:
                work->pendingBgmId = -1;
                if (work->command != 1) {
                    work->command = 2;
                }
                RequestSoundLoad(work->commandSoundId);
                break;
            default:
                work->command = 0;
                break;
            }
        }
        break;

    case 3:
        if (work->commandReady != 0) {
            s16 target = work->currentBgmId;
            u8 command;
            u8 soundId;

            PopQueuedSound();
            command = work->command;
            soundId = work->commandSoundId;

            switch (command) {
            case 0:
                break;
            case 1:
            case 2:
                work->pendingBgmId = -1;
                RequestSoundLoad(soundId);
                break;
            case 3:
                work->pendingBgmId = -1;
                PauseBgmForState(work->commandFadeFrames);
                break;
            case 4:
                work->pendingBgmId = -1;
                if (target == soundId) {
                    break;
                }
                if (target >= 0) {
                    work->currentBgmId = -1;
                    if (data_020559ec[target] == 1) {
                        NNS_SndPlayerReadVariable(&work->bgmHandle, 0, &work->savedSeqVar);
                        work->savedBgmId = target;
                    }
                    NNS_SndPlayerStopSeq(&work->bgmHandle, work->commandFadeFrames);
                    work->fadeTimer = work->commandFadeFrames;
                    work->phase = 4;
                } else {
                    RequestSoundLoad(soundId);
                }
                break;
            }
        }
        break;

    case 2:
        switch (work->command) {
        case 0:
            PopQueuedSound();
            break;
        case 1: {
            u8 command;

            if (GetRecentHistoryEntry(0) == 0) {
                break;
            }
            PopQueuedSound();
            command = work->command;
            if (command == 2 || command == 4) {
                u8 soundId = work->commandSoundId;
                if (work->currentBgmId != soundId) {
                    RequestSoundLoad(soundId);
                    break;
                }
            }
            if (command == 3) {
                work->pendingBgmId = -1;
                PauseBgmForState(work->commandFadeFrames);
            }
            break;
        }
        case 2:
        case 4: {
            BOOL resumed = FALSE;

            NNS_SndArcPlayerStartSeq(&work->bgmHandle, work->currentBgmId);
            if (data_020559ec[work->currentBgmId] == 1) {
                if (work->currentBgmId == work->savedBgmId) {
                    NNS_SndPlayerWriteVariable(&work->bgmHandle, 0, work->savedSeqVar);
                    NNS_SndPlayerMoveVolume(&work->bgmHandle, work->bgmVolume, 0x14);
                    resumed = TRUE;
                } else {
                    work->savedSeqVar = 0;
                    work->savedBgmId = work->currentBgmId;
                }
            }
            if (!resumed) {
                NNS_SndPlayerWriteVariable(&work->bgmHandle, 0, 0);
                NNS_SndPlayerMoveVolume(&work->bgmHandle, work->bgmVolume, 0);
            }
            work->command = 0;
            work->phase = 3;
            break;
        }
        case 3:
            break;
        }
        break;

    case 4: {
        int timer = work->fadeTimer;
        if (timer > 0) {
            work->fadeTimer = timer - 1;
        }
        if (work->fadeTimer != 0) {
            break;
        }
        if (work->command == 4) {
            RequestSoundLoad(work->commandSoundId);
        } else {
            work->command = 0;
            work->phase = 0;
        }
        break;
    }
    }

    {
        SoundSlot *slot = work->activeSlots;
        while (slot != NULL) {
            s16 playerNo = slot->playerNo;
            SoundSlot *next = slot->next;
            if (NNS_SndPlayerCountPlayingSeqByPlayerNo(playerNo) == 0) {
                FreeSoundHandleSlot(slot);
            } else {
                UpdateSoundSlotSpatial(slot);
            }
            slot = next;
        }
    }
    NNS_SndMain();
}

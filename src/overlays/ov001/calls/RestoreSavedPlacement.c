#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SessionFlags {
    u32 unk_0 : 2;
    u32 bit2 : 1;
    u32 bit3 : 1;
    u32 bit4 : 1;
    u32 bit5 : 1;
    u32 unk_6 : 4;
    u32 bit10 : 1;
    u32 bit11 : 1;
    u32 unk_12 : 2;
    u32 bit14 : 1;
    u32 unk_15 : 17;
} SessionFlags;

typedef struct SessionStatus {
    u8 active : 1;
    u8 unk_1 : 7;
} SessionStatus;

typedef struct SessionControl {
    s16 unk_00;
    s16 unk_02;
    s16 timer;
    s16 result;
    u32 unk_08;
    SessionFlags flags;
} SessionControl;

typedef struct Session {
    u8 pad_0000[0x1b];
    u8 redrawRequested;
    u8 pad_001C[0x208 - 0x1c];
    SessionControl control;
    u8 pad_0218[0x4];
    s32 choice;
    VecFx32 spawnPositions[3];
    u16 spawnAngles[3];
    u8 pad_024A[0x2748 - 0x24a];
    VecFx32 savedPositions[3];
    u16 savedAngles[3];
    u8 pad_2772[0x27b6 - 0x2772];
    SessionStatus status;
    u8 pad_27B7[0x27fd - 0x27b7];
    SessionStatus resumeStatus;
} Session;

extern Session *data_ov001_020a0480;
extern const VecFx32 data_ov001_0209e654[];
extern const s16 data_02053580[];
extern BOOL func_ov001_020645c8(u32 eventId);
extern void func_ov001_02064628(VecFx32 *position, u16 *angle);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void RefreshSelectionLinkValues(void);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

BOOL RestoreSavedPlacement(void)
{
    Session *session = data_ov001_020a0480;
    SessionControl *control = &session->control;
    MtxFx33 rotation;
    VecFx32 offset;
    int followerIndex;
    int angleIndex;

    if (func_ov001_020645c8(0x1a05)) {
        func_ov001_02064628(&session->savedPositions[0], &session->savedAngles[0]);
        session->spawnPositions[0] = session->savedPositions[0];
        session->spawnAngles[0] = session->savedAngles[0];
        if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
            for (followerIndex = 0; followerIndex < 2; followerIndex++) {
                offset = data_ov001_0209e654[followerIndex];
                MTX_Identity33_(&rotation);
                angleIndex = session->savedAngles[0] >> 4;
                MTX_RotY33_(&rotation, data_02053580[angleIndex], data_02053580[(0x400 - angleIndex) & 0xfff]);
                MTX_MultVec33(&offset, &rotation, &offset);
                VEC_Add(&offset, &session->savedPositions[0], &session->savedPositions[followerIndex + 1]);
                session->savedAngles[followerIndex + 1] = session->savedAngles[0];
                session->spawnPositions[followerIndex + 1] = session->savedPositions[followerIndex + 1];
                session->spawnAngles[followerIndex + 1] = session->savedAngles[followerIndex + 1];
            }
        }
        session->status.active = 1;
    }
    if (control->flags.bit4) {
        RefreshSelectionLinkValues();
    } else if (control->flags.bit2) {
        WriteSessionPackedBits(0x3534, 2, session->choice);
        if (session->choice == 1) {
            session->status.active = 0;
        }
    } else if (!control->flags.bit3) {
        if (control->flags.bit5) {
            if (control->flags.bit14) {
                session->choice = control->result;
                control->result = -2;
            }
        } else if (control->flags.bit10) {
            control->timer = 900;
            control->result = -4;
            control->flags.bit10 = 0;
            control->flags.bit11 = 1;
            data_ov001_020a0480->resumeStatus.active = 1;
        }
    }
    data_ov001_020a0480->redrawRequested = 1;
    return TRUE;
}

#include "nitro/types.h"

typedef struct ProfileData {
    s8 record[16];
    s8 name[22];
    u8 pad_26[0x67 - 0x26];
    u8 avatar;
    u8 rank;
    u8 pad_69[0x70 - 0x69];
} ProfileData;

typedef struct SceneArgs {
    u16 sceneId;
    u16 entry;
    u8 kind;
    u8 pad_05[2];
    u8 mode : 2;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 fromPanel : 1;
    u8 pad_7_5 : 3;
    u32 unk_08;
} SceneArgs;

typedef struct SessionInfo {
    u32 unk_00;
    u16 checksum;
    u16 exitMode : 3;
    u16 pad_6_3 : 2;
    u16 rank : 3;
    u16 avatar : 5;
    u16 hasBonus : 1;
    s8 stage;
    s8 world;
    u8 progress;
    u8 pad_0B[0x10 - 0xb];
    s8 base;
    s8 offset;
    s8 slot;
    u8 linked;
    u8 bonusFlag;
    u8 pad_15[3];
    u32 bonusValue;
} SessionInfo;

typedef struct PanelState {
    s8 slot;
    s8 phase;
    s8 world;
    u8 pad_03[0x2ee - 0x3];
    s8 base;
    s8 offset;
    s8 clearCount;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern SceneArgs data_02060850;
extern SessionInfo data_0206085c;
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern s32 func_ov013_02070cb4(void);
extern int DispatchContextCommand(u32 command, int value, int extra, void *buffer);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern BOOL func_ov002_02066c58(void);
extern void SetPendingScene(s32 pendId, s32 pendArg);

void LeavePanelScene(int exitMode) {
    ProfileData profile;
    u32 i;
    s8 *bytes;

    MI_CpuFill8(&profile, 0, sizeof(profile));
    if ((data_ov013_02074ce0->clearCount + 1) % 10 != 0) {
        DispatchContextCommand(0, func_ov013_02070cb4(), 0, &profile);
    }
    MI_CpuFill8(&data_02060850, 0, sizeof(data_02060850));
    data_02060850.sceneId = 900;
    data_02060850.entry = 4;
    data_02060850.kind = 3;
    data_02060850.mode = (u8)ReadGlobalPackedBits(0x1a00, 2);
    data_02060850.fromPanel = 1;
    data_0206085c.exitMode = (u16)exitMode;
    if (exitMode == 0) {
        data_0206085c.bonusFlag = 0;
        data_0206085c.bonusValue = 0;
    }
    data_0206085c.checksum = 0;
    bytes = profile.name;
    for (i = 0; i < 22; i++) {
        data_0206085c.checksum += bytes[i];
    }
    bytes = profile.record;
    for (i = 0; i < 16; i++) {
        data_0206085c.checksum += bytes[i];
    }
    data_0206085c.world = data_ov013_02074ce0->world;
    data_0206085c.stage = data_ov013_02074ce0->clearCount + 1;
    data_0206085c.rank = profile.rank;
    data_0206085c.avatar = profile.avatar;
    data_0206085c.hasBonus = (u16)DispatchContextCommand(5, 0, 0, NULL);
    data_0206085c.progress = DispatchContextCommand(7, 0, 0, NULL);
    data_0206085c.base = data_ov013_02074ce0->base;
    data_0206085c.offset = data_ov013_02074ce0->offset;
    data_0206085c.slot = data_ov013_02074ce0->slot;
    data_0206085c.linked = func_ov002_02066c58();
    SetPendingScene(2, 0);
    data_ov013_02074ce0->phase = 2;
}

#include "nitro/types.h"

typedef int (*SceneStateFunc)(void);

typedef struct SceneWork {
    u8 unknown_00[6];
    u16 flags;
    u8 unknown_08[0x10];
    int state;
    u8 unknown_1c[0x10];
    s16 sideCount;
} SceneWork;

extern SceneWork *data_ov035_020bc500;
extern SceneStateFunc gMovieSkipHandlers[];
extern void SaveSlotEntriesToBits(void);
extern int func_ov035_020bae94(void);
extern int ShowMovieMessage3700(void);
extern int func_ov035_020bafb4(void);
extern u32 GetBoundedEntryField(int index);
extern int GetMovieCounterLimit(int side);
extern int LoadMovieCounter(int side);
extern int GetScaledMenuLevel(int side);
extern void func_ov001_0207162c(int side, u16 value, int level, int scaled);
extern BOOL IsHudFlag9Set(void);
extern void UpdateChannelLevel(int side, u16 level);
extern void func_ov001_02074fa8(int side, u16 level, int mode);
extern void RefreshActiveMenuEntry(int side, u16 level, int mode);
extern void func_ov035_020ba7fc(int paused);
extern void func_ov035_020ba77c(void);

int RunMovieSceneFrame(void) {
    int side;
    int result;

    SaveSlotEntriesToBits();
    do {
        data_ov035_020bc500->flags &= 0x7fff;
        result = gMovieSkipHandlers[data_ov035_020bc500->state]();
        if (result >= 0) {
            data_ov035_020bc500->state = result;
        }
    } while (data_ov035_020bc500->flags & 0x8000);

    if (func_ov035_020bae94() == 0 && data_ov035_020bc500->sideCount > 0) {
        for (side = 0; side < 2; side++) {
            if (side == 0) {
                result = ShowMovieMessage3700();
            } else {
                result = func_ov035_020bafb4();
            }
            if (result != 0) {
                int value;
                int level;
                GetBoundedEntryField(0);
                value = GetMovieCounterLimit(side + 1);
                level = LoadMovieCounter(side + 1);
                func_ov001_0207162c(side + 1, value, level, GetScaledMenuLevel(side + 1));
                if (IsHudFlag9Set()) {
                    UpdateChannelLevel(side + 1, level);
                    func_ov001_02074fa8(side + 1, level, 7);
                } else {
                    RefreshActiveMenuEntry(side + 1, level, 7);
                }
            }
        }
    }
    if (data_ov035_020bc500->flags & 8) {
        func_ov035_020ba7fc(0);
    }
    if (data_ov035_020bc500->flags & 4) {
        func_ov035_020ba77c();
    }
    return 0;
}

#include "nitro/types.h"

typedef struct BoardState {
    char pad0000[0x64f0];
    void *listener;
    char pad64f4[4];
    int needsText;
    char pad64fc[0x66e0 - 0x64fc];
    int useChannel;
    char pad66e4[0x66fe - 0x66e4];
    s8 cursor;
} BoardState;

typedef void (*BoardCallback)(void);

extern BoardState *data_ov024_020b7540;
extern char sOv024_SYSMAPTASK_020b751c[];
extern void func_ov024_020b6e14(void);
extern void ReleaseSubObjectIfActive(void);
extern void SetupBoardTextLayer(void);
extern void func_ov024_020b6bd0(void);
extern void InvokeForChannelOrBoth(int channel, void *target, BoardCallback callback, int arg);
extern void *AddFieldListener(BoardCallback callback);

BoardCallback StartBoardScreen(void)
{
    BoardCallback next = NULL;

    if (data_ov024_020b7540->needsText) {
        next = func_ov024_020b6e14;
        SetupBoardTextLayer();
        data_ov024_020b7540->cursor = -1;
        func_ov024_020b6bd0();
    }
    if (data_ov024_020b7540->useChannel) {
        InvokeForChannelOrBoth(1, sOv024_SYSMAPTASK_020b751c, ReleaseSubObjectIfActive, 0);
    } else {
        data_ov024_020b7540->listener = AddFieldListener(ReleaseSubObjectIfActive);
    }
    return next;
}

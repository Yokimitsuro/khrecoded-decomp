#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

typedef struct {
    int x;
    int y;
    u16 *text;
    int charBase;
} PopupRequest;

typedef struct {
    u8 pad_00[0x2c];
    StateMachine machine;
    int x;
    int y;
    int charBase;
    u8 pad_44[0x78 - 0x44];
    u16 *text;
    u8 pad_7c[0x8c - 0x7c];
    PopupRequest queue[30];
    int queueCount;
} PopupWork;

extern PopupWork *data_ov093_020c5104;
extern void StateMachine_SetState(StateMachine *machine, int state);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void StartNextPopup(void)
{
    PopupWork *work = data_ov093_020c5104;

    work->machine.flags = 0;
    work->x = work->queue[0].x - 0x80;
    work->y = work->queue[0].y - 0x60;
    work->charBase = work->queue[0].charBase;
    work->text = work->queue[0].text;
    StateMachine_SetState(&work->machine, 2);
    MIi_CpuCopyFast(&data_ov093_020c5104->queue[1], &data_ov093_020c5104->queue[0],
                  sizeof(data_ov093_020c5104->queue));
    data_ov093_020c5104->queueCount--;
}

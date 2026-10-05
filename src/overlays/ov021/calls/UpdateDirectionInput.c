#include "nitro/types.h"

typedef struct DirectionInput {
    u16 angle;
    u16 prevAngle;
    u16 status;
    u8 active;
    u8 pad_07[7];
    u16 keys;
    u8 pad_10[7];
    u8 repeatPending;
    u8 repeatTimer;
} DirectionInput;

extern int func_ov001_02063a38(void);
extern int QuerySubModeStatus(void);

void UpdateDirectionInput(DirectionInput *input)
{
    int angle = -1;
    int count = 0;
    u16 keys;

    input->active = 0;
    if (func_ov001_02063a38() != 4) {
        if (input->keys & 0x40) {
            angle = 0;
            count++;
        } else if (input->keys & 0x80) {
            angle = 0x8000;
            count++;
        }
    }
    keys = input->keys;
    if (keys & 0x20) {
        angle += 0x4000;
        count++;
    } else if (keys & 0x10) {
        angle += ((keys & 0x40) ? 7 : 3) << 14;
        count++;
    }
    if (count > 0) {
        input->active = 1;
        input->prevAngle = input->angle;
        if (count <= 1) {
            input->angle = angle;
        } else {
            input->angle = angle >> 1;
        }
    } else {
        input->angle = 1;
    }
    if (input->repeatPending) {
        input->repeatTimer++;
        if (input->prevAngle == input->angle && input->active && input->repeatTimer < 15) {
            return;
        }
        input->repeatPending = 0;
        input->status = QuerySubModeStatus();
        if (input->active) {
            UpdateDirectionInput(input);
        }
    }
}

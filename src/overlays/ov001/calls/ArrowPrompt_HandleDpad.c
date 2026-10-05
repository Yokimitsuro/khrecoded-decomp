#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 pad_00[0xc];
    s32 active;
    u8 pad_10[0x10];
    u16 directions[3];
    u16 remaining : 14;
    u8 pad_28[0x4];
    s32 current;
} ArrowPrompt;

extern ArrowPrompt *data_ov001_020a04f0;
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern BOOL func_ov001_0207da80(ArrowPrompt *prompt);
extern void func_ov001_0207db18(ArrowPrompt *prompt);

int ArrowPrompt_HandleDpad(u32 keys)
{
    ArrowPrompt *prompt;
    int result;

    prompt = data_ov001_020a04f0;
    result = 4;
    if (prompt->remaining == 0) {
        result = 5;
    } else if (prompt->active == 0) {
        result = 5;
    } else if ((keys &= 0xf0) == 0) {
        result = 5;
    } else {
        switch (prompt->directions[prompt->current]) {
        case 0:
            if (keys & 0x40) {
                result = 0;
            }
            break;
        case 1:
            if (keys & 0x80) {
                result = 0;
            }
            break;
        case 2:
            if (keys & 0x20) {
                result = 0;
            }
            break;
        case 3:
            if (keys & 0x10) {
                result = 0;
            }
            break;
        }
        switch (result) {
        case 0:
        case 2:
            PlaySoundEffect(0, 0x42);
            if (func_ov001_0207da80(prompt)) {
                result = 1;
            }
            break;
        case 4:
            func_ov001_0207db18(prompt);
            break;
        }
    }
    return result;
}

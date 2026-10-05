#include "nitro/types.h"

typedef struct {
    u32 flag0 : 1;
    u32 flag1 : 1;
    u32 exitRequested : 1;
} ExitFlags;

extern int data_ov039_020bea20;
extern void func_ov039_020bcf40(int arg0);
extern void func_ov039_020bd074(int arg0);
extern void func_0204d808(int new_value);
extern BOOL IsSoundStreamActive(int handleIndex);
extern BOOL IsCachedSeqPlaying(void);
extern void SetCardThreadStartTick(void);
extern void RuntimeState_SetMode(int phase);

void UpdateExitSequence(void)
{
    int base = data_ov039_020bea20;

    func_ov039_020bcf40(*(int *)(base + 0xc998));
    func_ov039_020bd074(*(int *)(base + 0xc99c));
    if (!((ExitFlags *)(base + 0xc9e8))->exitRequested) {
        return;
    }
    if (*(int *)(base + 0xca34) != 0) {
        if (*(int *)(base + 0xca38) == 0) {
            func_0204d808(5);
            *(int *)(base + 0xca38) = 1;
        }
        if (IsSoundStreamActive(1)) {
            return;
        }
        if (IsCachedSeqPlaying()) {
            return;
        }
        RuntimeState_SetMode(9);
    } else if (*(int *)(base + 0xc994) == 3 && *(int *)(base + 0xca80) == 1) {
        if (IsSoundStreamActive(1)) {
            return;
        }
        SetCardThreadStartTick();
        RuntimeState_SetMode(9);
    } else {
        RuntimeState_SetMode(9);
    }
}

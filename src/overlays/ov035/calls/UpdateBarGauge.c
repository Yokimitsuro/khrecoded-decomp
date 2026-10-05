#include "nitro/types.h"

typedef struct BarGauge {
    const void *source;
    void *buffer;
    u8 unknown_08[0x128];
    int target;
    int current;
} BarGauge;

extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void DrawMovieDigitRow(void *buffer, u16 index, int style);
extern int NNS_GfdRegisterNewVramTransferTask(void *a, int b, int c, int d);

void UpdateBarGauge(BarGauge *gauge) {
    int current = gauge->current;
    int target = gauge->target;
    int i;

    if (target < current) {
        current -= 2;
        gauge->current = current;
        if (target < current) {
            target = current;
        }
        gauge->current = target;
    } else if (target > current) {
        current += 2;
        gauge->current = current;
        if (target > current) {
            target = current;
        }
        gauge->current = target;
    }
    MIi_CpuCopyFast(gauge->source, gauge->buffer, 0x160);
    for (i = 0; i < gauge->current; i++) {
        DrawMovieDigitRow(gauge->buffer, i, 0);
    }
    for (; i < 0x57; i++) {
        DrawMovieDigitRow(gauge->buffer, i, 1);
    }
    DrawMovieDigitRow(gauge->buffer, 0x22, 2);
    NNS_GfdRegisterNewVramTransferTask((void *)7, 0x50a0, (int)gauge->buffer, 0x160);
}

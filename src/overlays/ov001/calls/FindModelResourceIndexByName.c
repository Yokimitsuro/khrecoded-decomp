#include "nitro/types.h"

typedef struct ModelHolder {
    u8 pad_00[0x24];
    u8 *modelResource;
} ModelHolder;

extern char data_ov001_020a0504[];
extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern char *strcpy(char *dst, const char *src);
extern int NNS_G3dGetResDictIdxByName(const void *dict, const void *name);

int FindModelResourceIndexByName(ModelHolder *holder, const char *name)
{
    void *dict = NULL;

    MIi_CpuClear32(0, data_ov001_020a0504, 0x10);
    strcpy(data_ov001_020a0504, name);
    if (holder->modelResource != NULL) {
        dict = holder->modelResource + 0x40;
    }
    if (dict != NULL) {
        return NNS_G3dGetResDictIdxByName(dict, data_ov001_020a0504);
    }
    return -1;
}

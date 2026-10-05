#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x28];
    u8 *modelResource;
} ActorModel;

typedef struct ModelActor {
    u8 pad_00[0x10];
    ActorModel model;
} ModelActor;

extern char data_ov001_020a0518[];
extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern u32 strlen(const char *str);
extern char *strncpy(char *dst, const char *src, u32 count);
extern int NNS_G3dGetResDictIdxByName(const void *dict, const void *name);

u16 FindActorResourceIndexByName(ModelActor *actor, const char *name)
{
    ActorModel *model = &actor->model;
    void *dict = NULL;
    u32 length;

    if (name == NULL) {
        return 0xffff;
    }
    length = strlen(name);
    if (length >= 0x10) {
        return 0xffff;
    }
    MIi_CpuClear32(0, data_ov001_020a0518, 0x10);
    strncpy(data_ov001_020a0518, name, length);
    if (model->modelResource != NULL) {
        dict = model->modelResource + 0x40;
    }
    return dict != NULL ? NNS_G3dGetResDictIdxByName(dict, data_ov001_020a0518) : -1;
}

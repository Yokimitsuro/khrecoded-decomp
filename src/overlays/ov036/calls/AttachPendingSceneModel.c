#include "nitro/types.h"

typedef struct SceneWork {
    u8 pad_000[0xe7c];
    s32 pendingModel;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

typedef struct ModelViewer {
    u8 pad_000[0x24];
    u8 modelObject[0x74];
    s32 model;
    u8 pad_09C[0x90];
    int actorId;
    s32 unk_130;
    s32 unk_134;
} ModelViewer;

extern SceneContext data_ov036_020c3940;
extern void (*data_02060570)(const void *src, u32 dest, u32 size);
extern void LoadTextureInChunks(const void *src, u32 dest, u32 size);
extern void func_0202ed94(u8 *object, s32 value, s32 sourceB, void *extra);
extern void func_0202c6a4(int arg0);
extern void SetSceneModelBlendIndex(int actorId, s32 value);

void AttachPendingSceneModel(ModelViewer *viewer)
{
    viewer->model = data_ov036_020c3940.work->pendingModel;
    data_ov036_020c3940.work->pendingModel = 0;
    data_02060570 = LoadTextureInChunks;
    func_0202ed94(viewer->modelObject, viewer->model, 0, (void *)0xd);
    func_0202c6a4(1);
    SetSceneModelBlendIndex(viewer->actorId, 0);
    viewer->unk_130 = 0;
    viewer->unk_134 = 0;
}

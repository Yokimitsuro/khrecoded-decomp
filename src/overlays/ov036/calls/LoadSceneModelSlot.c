#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SharedRecord {
    u8 pad_00[0xc];
    int recordId;
} SharedRecord;

typedef struct ModelViewer {
    u8 pad_000[0x98];
    s32 model;
    u8 pad_09C[0x2c];
    VecFx32 position;
    u8 pad_0D4[0x54];
    s32 priority;
    int actorId;
    u8 pad_130[0x8];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
    u8 pad_0C84[0x1f8];
    SharedRecord *pendingModel;
    u8 pad_0E80[0x1d4];
    u32 archiveBase;
    u8 pad_1058[0x3c];
    ModelViewer *viewers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

#define ARCHIVE_FILE_ID(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

extern SceneContext data_ov036_020c3940;
extern int FindOrAcquireModelSlot(int actorId);
extern void AttachPendingSceneModel(ModelViewer *viewer);
extern BOOL IsRecordIdFree(int id);
extern int AcquireSharedRecord(u32 fileId, SharedRecord **out, int kind);
extern SharedRecord *SND_RegisterSeq(u32 fileId, int kind);

BOOL LoadSceneModelSlot(int actorId, s32 priority)
{
    SceneWork *work = data_ov036_020c3940.work;
    ModelViewer *viewer = &work->viewers[FindOrAcquireModelSlot(actorId)];

    if (viewer->model != 0) {
        return TRUE;
    }
    if (work->skipAnimations != 0) {
        return TRUE;
    }
    if (work->pendingModel == NULL) {
        if (work->skipAnimations != 0) {
            work->pendingModel = SND_RegisterSeq(ARCHIVE_FILE_ID(work->archiveBase, actorId), 0x11);
        } else {
            AcquireSharedRecord(ARCHIVE_FILE_ID(work->archiveBase, actorId), &work->pendingModel, 0x11);
        }
    } else if (IsRecordIdFree(work->pendingModel->recordId)) {
        VecFx32 position;

        AttachPendingSceneModel(viewer);
        viewer->priority = priority;
        position = viewer->position;
        position.z = (8 - viewer->priority) * 0xa000 + 0x5000;
        viewer->position = position;
        return TRUE;
    }
    return FALSE;
}

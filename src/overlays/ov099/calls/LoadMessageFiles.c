#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
    void *loadedFiles[3];
} SceneWork;

extern const char *gEnemyReportResourcePaths[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadMessageFiles(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        work->loadedFiles[i] = Msg_OpenContainerAndReadHeader(gEnemyReportResourcePaths[i], 0xe, FALSE);
    }
}

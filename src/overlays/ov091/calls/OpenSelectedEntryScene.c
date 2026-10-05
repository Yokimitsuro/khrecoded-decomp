#include "nitro/types.h"

typedef struct {
    s8 ids[5];
} EntrySceneTable;

typedef struct {
    int cursorRow;
} MenuScene;

extern EntrySceneTable data_ov091_020c2834;
extern BOOL func_ov091_020c1774(void);
extern void PushStackEntry(int value);
extern void StartSubScene(int scene, int arg, int mode);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OpenSelectedEntryScene(MenuScene *scene)
{
    EntrySceneTable scenes;

    if (func_ov091_020c1774()) {
        return;
    }
    scenes = data_ov091_020c2834;
    PushStackEntry(scene->cursorRow);
    StartSubScene(scenes.ids[scene->cursorRow], -1, 1);
    PlaySoundEffect(0, 1);
}

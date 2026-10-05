#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} MessageLoader;

typedef struct {
    u32 state;
    MessageLoader common;
    MessageLoader localized[3];
} MessageLoaderSet;

extern char sOv001_FormatS_0209eb70[];
extern char sOv001_BaEfInfoPZ_0209eb74[];
extern char sOv001_BaEfStLanguagePZ_0209eb84[];
extern void OS_SPrintf(char *dest, const char *format, ...);
extern char *Msg_BuildLangPath(const char *path);
extern void LoadAnimSetSlots(MessageLoader *loader, const char *path, int localized);
extern void func_ov001_0206c704(void (*callback)(void));
extern void RefreshMenuWindows(void);

void InitMessageLoaders(MessageLoaderSet *set)
{
    char path[128];
    int i;

    OS_SPrintf(path, sOv001_FormatS_0209eb70, sOv001_BaEfInfoPZ_0209eb74);
    i = 0;
    LoadAnimSetSlots(&set->common, path, 0);
    OS_SPrintf(path, sOv001_FormatS_0209eb70, Msg_BuildLangPath(Msg_BuildLangPath(sOv001_BaEfStLanguagePZ_0209eb84)));
    for (; i < 3; i++) {
        LoadAnimSetSlots(&set->localized[i], path, 1);
    }
    set->state = 0;
    func_ov001_0206c704(RefreshMenuWindows);
}

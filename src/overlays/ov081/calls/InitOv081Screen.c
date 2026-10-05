#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ObjManagerConfig {
    u32 cellFileId;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct Ov081State {
    u32 archive;
    u32 subArchive;
    StringTable stringsA;
    StringTable stringsB;
    u8 pad_20[0x63c6 - 0x20];
    s8 cursor;
    u8 pad_63c7;
    int page;
    u8 tween[0x18];
    u8 pad_63e4[4];
} Ov081State;

extern Ov081State *data_ov081_020c5da0;
extern const char sOv081_UiMenuTutorialP2_020c5d04[];
extern const char sOv081_UiMenuLanguageTutorialP2_020c5d18[];
extern const char sOv081_UiMenuStrLanguageTutoSZ_020c5d30[];
extern const char sOv081_UiMenuStrLanguageListSZ_020c5d48[];
extern const ObjManagerConfig data_ov081_020c5c64;
extern const ObjManagerConfig data_ov081_020c5c74;

extern void func_01ff88c4(void *dst, int value, u32 size);
extern int Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView(StringTable *table, const char *path, int flags);
extern void *func_ov039_020bc1dc(void);
extern void *func_ov039_020bc1ec(void);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b8fb8(void *container, u32 fileId, int count);
extern void func_ov027_020b9098(void *container, u32 fileId);
extern void *FindWidgetById(void *container, int id);
extern void func_ov027_020b97d8(void *container, void *widget, int mode);
extern void func_02052528(void *tween, int a, int b, int c, int duration);
extern void func_02052570(void *tween);
extern void LoadBitIndexTable(Ov081State *state);
extern void func_ov081_020c4280(Ov081State *state);
extern void BuildVisibleEntryIndex(Ov081State *state);
extern void SetupOv081Backgrounds(Ov081State *state);

int InitOv081Screen(Ov081State *state)
{
    void *container;
    ObjManagerConfig config;
    ObjManagerConfig subConfig;

    func_01ff88c4(state, 0, sizeof(Ov081State));
    data_ov081_020c5da0 = state;
    *(vu16 *)0x04000304 = (u16)(*(vu16 *)0x04000304 & ~0x8000);
    state->archive = Msg_OpenContainerAndReadHeader(sOv081_UiMenuTutorialP2_020c5d04, 0xe, FALSE);
    state->subArchive = Msg_OpenContainerAndReadHeader(sOv081_UiMenuLanguageTutorialP2_020c5d18, 0xe, FALSE);
    LoadPackedFileView(&state->stringsA, sOv081_UiMenuStrLanguageTutoSZ_020c5d30, 0);
    LoadPackedFileView(&state->stringsB, sOv081_UiMenuStrLanguageListSZ_020c5d48, 0);

    container = func_ov039_020bc1dc();
    config = data_ov081_020c5c64;
    config.cellFileId = ARCHIVE_FILE_ID(state->archive, 2);
    InitObjManagerAndMark(container, &config);
    func_ov027_020b8fb8(container, ARCHIVE_FILE_ID(state->archive, 3), 3);
    func_ov027_020b97d8(container, FindWidgetById(container, 0), 2);

    container = func_ov039_020bc1ec();
    subConfig = data_ov081_020c5c74;
    subConfig.cellFileId = ARCHIVE_FILE_ID(state->archive, 4);
    InitObjManagerAndMark(container, &subConfig);
    func_ov027_020b9098(container, ARCHIVE_FILE_ID(state->subArchive, 0));
    func_ov027_020b8fb8(container, ARCHIVE_FILE_ID(state->archive, 5), 0x15);

    func_02052528(state->tween, 0, 0, 0, 500);
    func_02052570(state->tween);
    LoadBitIndexTable(state);
    func_ov081_020c4280(state);
    BuildVisibleEntryIndex(state);
    state->cursor = 0;
    state->page = 0;
    SetupOv081Backgrounds(state);
    return 1;
}

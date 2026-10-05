#include "nitro/types.h"

typedef struct RoomSlots {
    s16 current;
    s16 entry;
    s16 next;
    s16 nextEntry;
    u8 pad_08[4];
    u32 unk0 : 4;
    u32 forceReload : 1;
} RoomSlots;

typedef struct SessionAudio {
    u8 channel[0x81c];
    void *message;
} SessionAudio;

typedef struct SessionState {
    u8 pad_000[0x1b];
    u8 loading;
    u8 pad_01c[0x1ec];
    RoomSlots room;
    u8 pad_218[0x32];
    s16 loadedEntry;
    u8 pad_24c[0x1cc4];
    SessionAudio audio;
} SessionState;

extern SessionState *data_ov001_020a0480;
extern char gFieldScriptCommandHandlers[];
extern char sOv001_MiMiDebugFormatD_0209e6d4[];
extern char sOv001_MiMiFormatD_0209e6e4[];
extern char data_ov001_0209e6f0[];
extern char sOv001_I_0209e6f4[];
extern void StoreGlobalArrayEntry(int index, char *value);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void func_ov001_02063560(s32 index, void *value);
extern void LoadSessionArchiveResource(void);
extern u16 LookupSessionKeyValue(int key);
extern void func_020257d8(void *channel, u32 source, u32 param);
extern void OpenSessionArchive(char *name, char *flag);
extern void SaveSessionCheckpoint(int id);
extern void func_ov001_020645e8(int flag);

int EnterPendingRoom(void) {
    SessionState *state = data_ov001_020a0480;
    char name[32];
    BOOL changed;
    SessionAudio *audio = &state->audio;
    RoomSlots *room = &state->room;

    changed = TRUE;

    if (room->next == state->room.current) {
        changed = FALSE;
    }
    StoreGlobalArrayEntry(2, gFieldScriptCommandHandlers);
    room->current = room->next;
    room->entry = room->nextEntry;
    if (room->entry >= 0) {
        WriteSessionPackedBits(0x3315, 10, room->entry);
    }
    if (changed) {
        if (room->next >= 1000) {
            OS_SPrintf(name, sOv001_MiMiDebugFormatD_0209e6d4, room->next);
        } else {
            OS_SPrintf(name, sOv001_MiMiFormatD_0209e6e4, room->next);
        }
        audio->message = Msg_OpenContainerAndReadHeader(name, 2, FALSE);
        func_ov001_02063560(0, audio->message);
        LoadSessionArchiveResource();
        func_020257d8(audio, LookupSessionKeyValue(-1), 2);
        OpenSessionArchive(data_ov001_0209e6f0, sOv001_I_0209e6f4);
    } else {
        func_020257d8(audio, LookupSessionKeyValue(room->entry), 2);
        OpenSessionArchive(NULL, sOv001_I_0209e6f4);
        room->nextEntry = -1;
    }
    if (state->loadedEntry != room->entry || room->forceReload) {
        SaveSessionCheckpoint(0x42);
    }
    data_ov001_020a0480->loading = 1;
    func_ov001_020645e8(0x3632);
    return 2;
}

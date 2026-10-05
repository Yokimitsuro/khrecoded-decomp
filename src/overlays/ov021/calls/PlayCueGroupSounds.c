#include "nitro/types.h"

typedef struct {
    s16 soundId;
    s16 volume;
} CueSound;

typedef struct {
    s32 time;
    u32 handle;
    CueSound **sounds;
    s8 mode;
    s8 range;
    s8 channel;
    s8 ownsHandle : 1;
    s8 stereo : 1;
    s8 pad_bits : 6;
} CueItem;

typedef struct {
    s16 id;
    s16 itemCount;
    CueItem **items;
} CueGroup;

typedef struct {
    u8 pad_00[0x14];
    u32 (*play)(int owner, int soundId, int volume, u32 flags);
    s32 (*getVolume)(int owner);
    s8 owner;
    u8 pad_1d[3];
    s32 groupId;
    u32 *current;
    s32 exclusiveId;
    s32 altSoundA;
    s32 altSoundB;
    s32 bgmId;
} CueTable;

extern void StopCueGroupSounds(CueTable *table, int groupId);
extern BOOL func_0204dc50(u32 handle);
extern void Handle_WritePayloadIfLive(u32 handle, s32 volume);
extern CueGroup *FindTableEntryById(CueTable *table, int id);
extern u32 func_0202a9e4(u32 range);
extern int GetCurrentSceneId(void);
extern u32 func_ov001_02066e70(void);
extern void StopSoundSeqHandle(u32 handle);

void PlayCueGroupSounds(CueTable *table, int groupId, s32 time)
{
    int i;
    CueGroup *group;

    StopCueGroupSounds(table, groupId);
    if (table->groupId != groupId) {
        table->groupId = groupId;
    }
    if (table->current != NULL) {
        if (!func_0204dc50(*table->current)) {
            table->current = NULL;
        } else if (table->getVolume != NULL) {
            Handle_WritePayloadIfLive(*table->current, table->getVolume(table->owner));
        }
    }
    group = FindTableEntryById(table, groupId);
    if (group == NULL) {
        return;
    }
    for (i = 0; i < group->itemCount; i++) {
        CueItem *item = group->items[i];
        CueSound *sound = NULL;
        s32 choice = -1;
        u32 flags = 0;
        BOOL exclusive;
        s32 soundId;

        if (item->time > time || item->channel >= 0) {
            continue;
        }
        switch (item->mode) {
        case 0:
            choice = 0;
            break;
        case 1:
            choice = func_0202a9e4(item->range);
            break;
        }
        if (choice >= 0) {
            sound = item->sounds[choice];
            if (item->stereo) {
                flags |= 2;
            }
        }
        if (sound == NULL) {
            continue;
        }
        soundId = sound->soundId;
        exclusive = FALSE;
        switch (soundId) {
        case 0:
        case 4:
        case 0x15:
        case 0x23:
            break;
        case 0x48:
        case 0x53:
        case 0x54:
            soundId = table->altSoundA;
            break;
        case 0x34:
            soundId = table->bgmId;
            break;
        case 0x55:
            soundId = table->altSoundB;
            break;
        }
        if (table->exclusiveId == soundId || table->bgmId == soundId) {
            if (GetCurrentSceneId() == 2 && func_ov001_02066e70()) {
                continue;
            }
            if (table->bgmId == soundId) {
                if (table->current != NULL) {
                    StopSoundSeqHandle(*table->current);
                }
            } else if (table->current != NULL) {
                continue;
            }
            exclusive = TRUE;
        }
        if (soundId < 0) {
            continue;
        }
        item->handle = table->play(table->owner, soundId, sound->volume, flags);
        item->channel = choice;
        if (exclusive) {
            table->current = &item->handle;
        }
    }
}

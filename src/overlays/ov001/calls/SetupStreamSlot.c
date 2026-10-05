#include "nitro/types.h"

typedef struct {
    s32 frame;
    s16 id;
    s32 param;
    char name[1];
} StreamSlot;

typedef struct {
    u8 pad_000[0xd18];
    u8 **animHolder;
    u8 pad_d1c[4];
    void *message;
    u8 pad_d24[0xef4 - 0xd24];
    u32 flags;
    u8 pad_ef8[8];
    u32 actorId;
} StreamOwner;

extern char data_ov001_0209f310[];
extern char *strcpy(char *dst, const char *src);
extern int strlen(const char *str);
extern int strcmp(const char *str1, const char *str2);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern int func_0202f4cc(void *anim, u16 index);
extern int Anim_GetFrame(void *anim, u16 index);
extern int ActorSlot_GetField1C4ByIndex(u16 id);

BOOL SetupStreamSlot(StreamOwner *owner, StreamSlot *slot, const char *name, s16 id, int animIndex, s32 param, BOOL clampHalf)
{
    if (slot->id == -1) {
        slot->id = id;
        if (name == 0 || name[0] == 0) {
            slot->name[0] = 0;
        } else {
            strcpy(slot->name, name);
            if (strcmp(slot->name + (strlen(slot->name) - 3), data_ov001_0209f310) == 0
                && owner->message == 0) {
                owner->message = Msg_OpenContainerAndReadHeader(name, 0xd, FALSE);
            }
        }
        slot->param = param;
        if (animIndex == 0) {
            int length = func_0202f4cc(*owner->animHolder + 4, animIndex);
            int frame = Anim_GetFrame(*owner->animHolder + 4, animIndex);
            if (clampHalf) {
                if (frame < length / 2) {
                    slot->frame = length / 2;
                } else {
                    slot->frame = length;
                }
            } else {
                slot->frame = length;
                if (!(owner->flags & 0x40)) {
                    slot->frame -= ActorSlot_GetField1C4ByIndex(owner->actorId);
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

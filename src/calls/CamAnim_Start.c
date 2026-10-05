#include "nitro/types.h"

typedef struct {
    u32 flags;
    void *resource;
    void *player;
    u8 pad_0c[0x3c];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} CameraAnim;

extern void *SND_RegisterSeq(int fileId, int kind);
extern void *CamAnim_AllocPlayer(void);
extern void CamAnim_SelectAnim(CameraAnim *anim, int animIndex);
extern void func_0203a8ec(CameraAnim *anim);
extern void CamAnim_Update(CameraAnim *anim);

void CamAnim_Start(CameraAnim *anim, int fileId)
{
    anim->flags = 0;
    anim->unk_54 = 0;
    anim->resource = SND_RegisterSeq(fileId, 0x11);
    anim->player = CamAnim_AllocPlayer();
    CamAnim_SelectAnim(anim, 0);
    func_0203a8ec(anim);
    CamAnim_Update(anim);
    anim->unk_48 = 0;
    anim->unk_4C = 0;
    anim->unk_50 = 0;
    anim->flags |= 1;
}

#include "nitro/types.h"

typedef struct TextureResource {
    u8 pad_00[0x20];
    u16 texInfoFlags;
} TextureResource;

typedef struct SceneTextureState {
    u8 pad_00[0x20];
    u32 texSize;
    u32 plttSize;
    u32 texKey;
    u32 plttKey;
} SceneTextureState;

extern SceneTextureState *data_ov001_020a04a0;
extern u32 (*sDefaultAllocTexVramFunc)(u32 size, BOOL is4x4comp, u32 opt);
extern u32 (*sDefaultAllocPlttVramFunc)(u32 size, BOOL is4pltt, u32 opt);

extern void func_0202c6a4(int enable);
extern TextureResource *NNS_G3dGetTex(void *file);
extern u32 NNS_G3dTexGetRequiredSize(TextureResource *tex);
extern u32 NNS_G3dPlttGetRequiredSize(TextureResource *tex);
extern void NNS_G3dTexSetTexKey(TextureResource *tex, u32 texKey, u32 tex4x4Key);
extern void Obj_SetWord2C(TextureResource *tex, u32 plttKey);
extern void Tex_LoadVram(TextureResource *tex);
extern void func_0202d218(TextureResource *tex);

void LoadSceneTextureResource(void *file)
{
    SceneTextureState *state = data_ov001_020a04a0;
    TextureResource *tex;
    u32 texSize;
    u32 plttSize;

    func_0202c6a4(0);
    tex = NNS_G3dGetTex(file);
    texSize = NNS_G3dTexGetRequiredSize(tex);
    plttSize = NNS_G3dPlttGetRequiredSize(tex);
    if (state->texKey == 0) {
        state->texKey = sDefaultAllocTexVramFunc(texSize, FALSE, 0);
    }
    if (state->plttKey == 0) {
        state->plttKey = sDefaultAllocPlttVramFunc(plttSize, tex->texInfoFlags & 0x8000, 0);
    }
    NNS_G3dTexSetTexKey(tex, state->texKey, 0);
    Obj_SetWord2C(tex, state->plttKey);
    Tex_LoadVram(tex);
    func_0202d218(tex);
    state->texSize = texSize;
    state->plttSize = plttSize;
    func_0202c6a4(1);
}

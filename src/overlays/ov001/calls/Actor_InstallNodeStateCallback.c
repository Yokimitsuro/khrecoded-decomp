#include "nitro/types.h"

struct NNSG3dRS_;
typedef void (*SbcCallback)(struct NNSG3dRS_ *);

typedef struct RenderObj {
    u8 pad_00[0x2c];
    void *userData;
} RenderObj;

typedef struct SceneObject {
    u8 pad_00[0x24];
    RenderObj renderObj;
} SceneObject;

typedef struct ActorBody {
    SceneObject *object;
} ActorBody;

typedef struct Actor {
    u8 pad_000[0x700];
    u8 nodeState[0x618];
    ActorBody *body;
    u8 pad_d1c[0xf00 - 0xd1c];
    int useAltCallback;
} Actor;

extern void NNS_G3dRenderObjResetCallBack(RenderObj *renderObj);
extern void NNS_G3dRenderObjSetCallBack(RenderObj *renderObj, SbcCallback callback, u8 *unused, u8 cmd, int timing);
extern void func_ov001_0208985c(struct NNSG3dRS_ *rs);
extern void func_ov001_0208974c(struct NNSG3dRS_ *rs);

void Actor_InstallNodeStateCallback(Actor *actor)
{
    RenderObj *renderObj = &actor->body->object->renderObj;

    NNS_G3dRenderObjResetCallBack(renderObj);
    renderObj->userData = actor->nodeState;
    if (actor->useAltCallback == 0) {
        NNS_G3dRenderObjSetCallBack(renderObj, func_ov001_0208985c, NULL, 6, 3);
        return;
    }
    NNS_G3dRenderObjSetCallBack(renderObj, func_ov001_0208974c, NULL, 6, 3);
}

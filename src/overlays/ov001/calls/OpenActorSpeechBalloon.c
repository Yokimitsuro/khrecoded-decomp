#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct {
    u8 pad_00[0x80];
    fx32 depth;
} CameraChannel;

typedef struct {
    u8 pad_00[0x50];
    int balloonStyle;
} BalloonState;

typedef struct {
    u8 pad_000[0x1c8];
    BalloonState *balloon;
} ScriptContext;

extern int func_ov001_02088b48(int actorId);
extern int func_ov001_02063a38(void);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern BOOL ActorSlot_GetByIndex(u16 actorId);
extern fx32 GetActorModeThreeTarget(int actorId);
extern CameraChannel *ActorChannel_SelectBuffer(void);
extern void func_ov001_02088ab0(const VecFx32 *worldPos, int *screenX, int *screenY);
extern void OpenType8BalloonAtPosition(int style, const VecFx32 *worldPos, void *message, void *options);
extern void OpenType9BalloonAtPosition(const VecFx32 *worldPos, void *message);

void OpenActorSpeechBalloon(ScriptContext *context, void *message, int actorId) {
    VecFx32 *anchor;
    int screenX;
    int screenY;
    VecFx32 headPos;
    VecFx32 position;
    fx32 depth;

    context->balloon->balloonStyle = func_ov001_02088b48(actorId);
    if (func_ov001_02063a38() == 4 || func_ov001_02063a38() == 7 || context->balloon->balloonStyle == 0) {
        fx32 height;

        if (actorId == -1) {
            OpenType8BalloonAtPosition(context->balloon->balloonStyle, NULL, message, NULL);
            return;
        }
        headPos = ActorRegistry_GetEntityByIndex(actorId)->position;
        if (func_ov001_02063a38() == 4) {
            headPos.y += GetActorModeThreeTarget(actorId) + 0x1800;
        } else if (func_ov001_02063a38() == 7) {
            headPos.y += 0x2000;
        } else {
            height = GetActorModeThreeTarget(actorId) + 0xb33;
            if (height < 0x1800) {
                height = 0x1800;
            }
            if (actorId == 0) {
                height += 0x333;
            }
            headPos.y += height;
        }
        OpenType9BalloonAtPosition(&headPos, message);
        return;
    }
    anchor = NULL;
    if (actorId != -1 && ActorSlot_GetByIndex(actorId)) {
        depth = ActorChannel_SelectBuffer()->depth;
        position = ActorRegistry_GetEntityByIndex(actorId)->position;
        anchor = &position;
        func_ov001_02088ab0(anchor, &screenX, &screenY);
        if (depth < 0x44cd && depth > 0x3800) {
            if (screenX < 0 || screenX > 0xff || screenY > 0xff) {
                anchor = NULL;
            } else if (context->balloon->balloonStyle == 1 && screenY >= 0xc0) {
                position.y += 0x2000;
                OpenType9BalloonAtPosition(anchor, message);
                return;
            }
        } else if (screenY < 0) {
            anchor = NULL;
        }
    }
    OpenType8BalloonAtPosition(context->balloon->balloonStyle, anchor, message, NULL);
}

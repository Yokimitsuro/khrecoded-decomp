#include "nitro/types.h"

typedef struct SceneMessage {
    u8 data[4];
} SceneMessage;

typedef struct SceneTextOwner {
    u8 pad_000[0x550];
    SceneMessage message;
} SceneTextOwner;

extern BOOL DrawNextTypewriterGlyph(SceneMessage *writer);
extern void CloseSceneMessage(SceneMessage *message);

void FlushAndCloseSceneMessage(SceneTextOwner *owner)
{
    SceneMessage *message = &owner->message;

    while (DrawNextTypewriterGlyph(message)) {
    }
    CloseSceneMessage(message);
}

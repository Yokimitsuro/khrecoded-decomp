#include "nitro/types.h"

typedef struct PanelNode {
    u8 pad_00[8];
    u8 *entity;
    u8 pad_0c[0x32 - 0x0c];
    u8 actorId;
    u8 pad_33[0x48 - 0x33];
    void *animation;
    u8 pad_4c[4];
    u8 state;
    u8 pad_51[3];
    u16 flags;
} PanelNode;

extern u16 AdvanceAnimationTracks(void *state, int delta);
extern u8 *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_RemoveFromQuadTree(void *entity);

int UpdatePanelAnimations(PanelNode *node)
{
    if ((node->flags & 0x20) && AdvanceAnimationTracks(node->animation, 0x1000)) {
        node->flags &= 0xffdf;
    }
    if (node->flags & 0x10) {
        if (AdvanceAnimationTracks(ActorRegistry_GetEntityByIndex(node->actorId) + 4, 0x1000)) {
            node->flags &= 0xffaf;
        }
    }
    if (!(node->flags & 0x30)) {
        node->state = 2;
        if (!(node->flags & 1)) {
            Obj_RemoveFromQuadTree(node->entity + 0x10);
        }
    }
    return 0;
}

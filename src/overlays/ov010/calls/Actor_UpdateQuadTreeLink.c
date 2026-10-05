#include "nitro/types.h"

extern u32 GetActorRegistry(void);
extern int FX_Mul(int left, int right);
extern u32 Obj_UpdateQuadTreeLink(u32 world, void *entity, u32 arg);
extern void QuadTree_RemoveObject(int *tree, int node);

void Actor_UpdateQuadTreeLink(int actor, int speedDelta)
{
    u32 world;
    int scaledSpeed;
    int worldPtr;

    world = GetActorRegistry();
    scaledSpeed = FX_Mul(speedDelta, (int)*(short *)(actor + 0x1c4));
    Obj_UpdateQuadTreeLink(world, (void *)(actor + 0x10), scaledSpeed);
    worldPtr = GetActorRegistry();
    QuadTree_RemoveObject((int *)**(int **)(worldPtr + 4), actor + 0x11c);
}

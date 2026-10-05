extern void Obj_Release(void *context);
extern void DestroyAllContainerElements(void *context);

typedef struct {
    char pad[25720];
    unsigned int flags;
} Unk02054364;

void DestroyObjectsAndRelease(Unk02054364 *context)
{
    DestroyAllContainerElements(context);

    if (((context->flags << 29) >> 31) == 1) {
        Obj_Release(context);
        context->flags &= ~4;
    }
}

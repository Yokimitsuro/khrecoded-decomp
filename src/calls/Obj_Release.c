extern void Slot_UnlinkAll(void *);
extern void FreeAndClearNodeList(void *);

int Obj_Release(void *object)
{
    Slot_UnlinkAll(object);
    FreeAndClearNodeList(object);
    return 1;
}

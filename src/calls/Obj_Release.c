extern void Slot_UnlinkAll(void *);
extern void func_0204ef20(void *);

int Obj_Release(void *object)
{
    Slot_UnlinkAll(object);
    func_0204ef20(object);
    return 1;
}

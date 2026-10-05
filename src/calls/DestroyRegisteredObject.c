extern int  SetDefaultHeap(int arena);
extern void unlink_object_registry_node(int node);
extern void NNSi_FndFreeFromDefaultHeap(void *unknown_argument_p);
extern void NNSi_FndFreeToExpHeap(void *obj, void *heap);
extern int  data_020603c8[];
extern int  data_02060394[];

int DestroyRegisteredObject(int *object)
{
    int saved_value;
    void (*destructor)(void);
    int arena_state;

    arena_state = SetDefaultHeap(object[7]);
    saved_value = data_020603c8[1];
    data_020603c8[1] = (int)object;
    destructor = (void (*)(void))object[6];
    if (destructor != 0) {
        destructor();
    }
    *object = 0;
    data_020603c8[1] = saved_value;
    unlink_object_registry_node((int)object);
    saved_value = object[3];
    if (object[8] != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)object[8]);
    }
    NNSi_FndFreeToExpHeap(object, (void *)data_02060394[0]);
    SetDefaultHeap(arena_state);
    return saved_value;
}

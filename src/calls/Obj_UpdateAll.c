extern int  SetDefaultHeap(int arena);
extern int  DestroyRegisteredObject(int *obj);
extern int  data_020603c8[];

void Obj_UpdateAll(int paused)
{
    int *obj;
    int next;

    data_020603c8[1] = data_020603c8[3];
    obj = (int *)data_020603c8[1];
    while (obj != 0) {
        switch (obj[5]) {
        case -2:
            next = obj[3];
            if (!(obj[0] & 1)) {
                next = DestroyRegisteredObject(obj);
            }
            break;
        case -1:
            next = obj[3];
            break;
        default:
            if (paused == 0 || (obj[0] & 4)) {
                int arena = SetDefaultHeap(obj[7]);
                int cb = ((int (*)(void))((int *)data_020603c8[1])[5])();

                SetDefaultHeap(arena);
                if (cb != 0) {
                    ((int *)data_020603c8[1])[5] = cb;
                }
            }
            next = ((int *)data_020603c8[1])[3];
            break;
        }
        data_020603c8[1] = next;
        obj = (int *)next;
    }
    data_020603c8[1] = 0;
    if (paused == 0) {
        data_020603c8[2]++;
    }
}

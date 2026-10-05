extern int  SetDefaultHeap(int arena);
extern int  DestroyRegisteredObject(int *obj);
extern int  gTaskManager[];

void Obj_UpdateAll(int paused)
{
    int *obj;
    int next;

    gTaskManager[1] = gTaskManager[3];
    obj = (int *)gTaskManager[1];
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
                int cb = ((int (*)(void))((int *)gTaskManager[1])[5])();

                SetDefaultHeap(arena);
                if (cb != 0) {
                    ((int *)gTaskManager[1])[5] = cb;
                }
            }
            next = ((int *)gTaskManager[1])[3];
            break;
        }
        gTaskManager[1] = next;
        obj = (int *)next;
    }
    gTaskManager[1] = 0;
    if (paused == 0) {
        gTaskManager[2]++;
    }
}

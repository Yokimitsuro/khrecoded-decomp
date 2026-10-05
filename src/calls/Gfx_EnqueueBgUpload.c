extern int GetBGExtPlttSlot_0202aef8(int a0, int a1, int a2);
extern int Gfx_EnqueueBgCharUpload(int a0, int a1);
extern int Gfx_EnqueueBgScreenUpload(int a0, int a1);

int Gfx_EnqueueBgUpload(int arg0, int arg1, int arg2)
{
    if (arg1 != 0) {
        return Gfx_EnqueueBgCharUpload(GetBGExtPlttSlot_0202aef8(arg0, arg1, arg2), arg2);
    }
    return Gfx_EnqueueBgScreenUpload(arg0, arg2);
}

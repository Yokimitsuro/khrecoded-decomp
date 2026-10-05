extern int func_0202aef8(int a0, int a1, int a2);
extern int func_0202aeac(int a0, int a1);
extern int func_0202aed4(int a0, int a1);

int Gfx_EnqueueBgUpload(int arg0, int arg1, int arg2)
{
    if (arg1 != 0) {
        return func_0202aeac(func_0202aef8(arg0, arg1, arg2), arg2);
    }
    return func_0202aed4(arg0, arg2);
}

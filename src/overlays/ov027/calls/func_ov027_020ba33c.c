extern int func_ov027_020ba2c8(int arg0, int arg1);
extern void Text_VSNPrintfWide(int arg0, int arg1, int arg2, int arg3);

int func_ov027_020ba33c(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    int value = func_ov027_020ba2c8(arg0, arg1);
    Text_VSNPrintfWide(arg2, arg3, value, arg4);
    return arg2;
}

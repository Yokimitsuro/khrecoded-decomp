extern char data_02055788[];

void func_0202b3e8(int index, int arg1, int arg2, int arg3) {
    void (*callback)(int arg1, int arg2, int arg3);

    callback = *(void (**)(int, int, int))(data_02055788 + index * 0x18);
    if (callback != 0) {
        callback(arg1, arg2, arg3);
    }
}

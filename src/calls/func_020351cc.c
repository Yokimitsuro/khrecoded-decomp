extern void func_01ffce24(int handle, int object);

void func_020351cc(int handle, int object) {
    *(unsigned int *)(object + 8) = 0;
    func_01ffce24(handle, object);
}

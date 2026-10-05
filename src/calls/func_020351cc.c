extern void QueryModelCollision(int handle, int object);

void func_020351cc(int handle, int object) {
    *(unsigned int *)(object + 8) = 0;
    QueryModelCollision(handle, object);
}

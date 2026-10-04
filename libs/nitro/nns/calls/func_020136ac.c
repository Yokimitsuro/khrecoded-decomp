/* Allocator vtable hook: allocates from the expanded heap at allocator+4 with the
 * alignment stored at allocator+8. */
extern void *NNS_FndAllocFromFrmHeapEx();

void *func_020136ac(void **allocator, unsigned int size) {
    return NNS_FndAllocFromFrmHeapEx(allocator[1], size, allocator[2]);
}

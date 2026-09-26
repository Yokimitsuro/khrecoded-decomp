/* Allocator vtable hook: allocates from the expanded heap at allocator+4 with the
 * alignment stored at allocator+8. */
extern void *func_0201351c();

void *func_020136ac(void **allocator, unsigned int size) {
    return func_0201351c(allocator[1], size, allocator[2]);
}

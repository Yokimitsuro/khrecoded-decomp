/* Ends the overlay and always reports success. */
extern void FS_EndOverlay(void *p);

int func_0200bd68(void *p) {
    FS_EndOverlay(p);
    return 1;
}

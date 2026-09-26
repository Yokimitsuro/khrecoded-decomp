extern void *OSi_DoLockByWord();

void *func_020021b8(int id, void *word, void *callback) {
    return OSi_DoLockByWord(id, word, callback, 0);
}

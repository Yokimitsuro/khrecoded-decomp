extern void *OSi_DoTryLockByWord();

void *func_020022b8(int id, void *word, void *callback) {
    return OSi_DoTryLockByWord(id, word, callback, 0);
}

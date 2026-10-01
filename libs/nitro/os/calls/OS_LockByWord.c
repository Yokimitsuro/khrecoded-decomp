extern void *OSi_DoLockByWord();

void *OS_LockByWord(int id, void *word, void *callback) {
    return OSi_DoLockByWord(id, word, callback, 0);
}

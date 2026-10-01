extern void *OSi_DoUnlockByWord();

void *OS_UnlockByWord(int id, void *word, void *callback) {
    return OSi_DoUnlockByWord(id, word, callback, 0);
}

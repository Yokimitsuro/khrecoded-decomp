extern void *OSi_DoUnlockByWord();

void *func_0200223c(int id, void *word, void *callback) {
    return OSi_DoUnlockByWord(id, word, callback, 0);
}

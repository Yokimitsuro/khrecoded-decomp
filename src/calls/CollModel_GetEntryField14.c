extern int *CollModel_FindEntry(void *model, void *key);

int CollModel_GetEntryField14(void *model, void *key) {
    return CollModel_FindEntry(model, key)[5];
}

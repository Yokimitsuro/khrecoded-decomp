extern char *FindEntryByNameNoCase(int arg0, void *);

char *CollModel_FindEntry(void *p, void *key)
{
    return FindEntryByNameNoCase(*(int *)*(int **)((char *)p + 4), key);
}

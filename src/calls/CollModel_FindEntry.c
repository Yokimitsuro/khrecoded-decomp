extern char *func_02033878(int arg0, void *);

char *CollModel_FindEntry(void *p, void *key)
{
    return func_02033878(*(int *)*(int **)((char *)p + 4), key);
}

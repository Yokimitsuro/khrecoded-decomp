extern int func_02025df8(void *a, void *b);
extern int func_0204d684(int x);

int func_020267b8(void *p, char *buf)
{
    int saved;
    saved = func_02025df8(p, buf);
    func_02025df8(p, buf + 8);
    func_0204d684(saved);
    return 1;
}

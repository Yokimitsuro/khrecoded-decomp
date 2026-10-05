extern int ScriptVm_ReadOperandInt(void *a, void *b);
extern int func_0204d684(int x);

int func_020267b8(void *p, char *buf)
{
    int saved;
    saved = ScriptVm_ReadOperandInt(p, buf);
    ScriptVm_ReadOperandInt(p, buf + 8);
    func_0204d684(saved);
    return 1;
}

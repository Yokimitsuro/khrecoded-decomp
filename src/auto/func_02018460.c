unsigned short func_02018460(unsigned short **p)
{
    unsigned short *q = *p;
    unsigned short v = *q++;
    *p = q;
    return v;
}

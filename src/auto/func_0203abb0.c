struct T { int a, b, c; };
struct S { int pad[18]; struct T t; };

void func_0203abb0(struct S *d, struct T *s)
{
    d->t = *s;
}

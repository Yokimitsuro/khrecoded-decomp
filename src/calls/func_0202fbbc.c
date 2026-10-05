extern void QuaternionToRotationMatrix(void *mtx);
extern void func_01ff9404(void *out, void *mtx, void *in);

void func_0202fbbc(void *in_vec, int unused, void *out_vec)
{
    int mtx_local[9];
    QuaternionToRotationMatrix(&mtx_local);
    func_01ff9404(out_vec, &mtx_local, in_vec);
}

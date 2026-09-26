extern int data_0205a8c4[];
extern void *data_02055c54;
extern void *data_02055c58;
extern void func_02013d88(int value);
extern void func_02013c2c(void);
extern void func_02013d48(void);

void func_02013be0(int value, int install_callbacks) {
    data_0205a8c4[2] = value;
    func_02013d88(value);

    if (install_callbacks != 0) {
        data_02055c54 = func_02013c2c;
        data_02055c58 = func_02013d48;
    }
}

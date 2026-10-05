typedef struct Overlay088GridSettings { int resource; int unknown[3]; } Overlay088GridSettings;
extern const Overlay088GridSettings data_ov088_020bee6c;
extern const int data_ov088_020beec0[6][3];
extern void *func_ov039_020bc1ec(void);
extern int BuildSlotImageParams(int group, int index);
extern void InitObjManagerAndMark(void *grid, Overlay088GridSettings *settings);
extern void func_ov027_020b8fb8(void *grid, int resource, int count);
extern void SetAllElementObjectModes(void *grid, int mode);
extern unsigned int ReadSessionPackedBits(int id, int bits);
extern int FindWidgetById(void *grid, int id);
extern void func_ov027_020b9604(void *grid, int entry);
extern void func_ov027_020b96c0(void *grid, int entry, unsigned short state);
void ApplyOverlay088GridStates(void *unusedContext) {
    void *grid = func_ov039_020bc1ec();
    Overlay088GridSettings settings = data_ov088_020bee6c;
    int stateBits;
    int row, column, entry;
    int enabled;
    settings.resource = BuildSlotImageParams(2, 0x13);
    InitObjManagerAndMark(grid, &settings);
    func_ov027_020b8fb8(grid, BuildSlotImageParams(2, 0x15), 0x18);
    SetAllElementObjectModes(grid, 2);
    stateBits = ReadSessionPackedBits(0x1e05, 18);
    for (row = 0; row < 6; ++row) {
        for (column = 0; column < 3; ++column) {
            if (stateBits & (1U << (17 - (column + row * 3)))) enabled = 1;
            else enabled = 0;
            entry = FindWidgetById(grid, data_ov088_020beec0[row][column]);
            func_ov027_020b9604(grid, entry);
            func_ov027_020b96c0(grid, entry, enabled);
        }
    }
}

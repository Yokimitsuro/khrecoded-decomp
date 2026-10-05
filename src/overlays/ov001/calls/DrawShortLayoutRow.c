extern void BlitNibbleRunPadded(int a, int b, int width, int height,
                                int flags, int style, void *row);

typedef struct {
    unsigned char bytes[5];
} Ov002ShortRow;

extern Ov002ShortRow data_ov001_0209de47[];

void DrawShortLayoutRow(int a, int b, int row) {
    BlitNibbleRunPadded(a, b, 5, 110, 0, 1, &data_ov001_0209de47[row]);
}

typedef unsigned short u16;

typedef struct MaterialColorScale {
    u16 red;
    u16 green;
    u16 blue;
} MaterialColorScale;

extern MaterialColorScale data_027e01f0;
extern u16 data_027e01ec;

void func_01fff67c(int value)
{
    data_027e01ec = 1;
    data_027e01f0.red = (value & 0x1f) + 1;
    data_027e01f0.green = ((value >> 5) & 0x1f) + 1;
    data_027e01f0.blue = ((value >> 10) & 0x1f) + 1;
}

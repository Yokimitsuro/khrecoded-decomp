extern int FloorMod(int a, int b);

int func_02022584(int value)
{
    if (FloorMod(value, 4) == 0) {
        if (FloorMod(value, 100) != 0 || FloorMod(value, 400) == 100) {
            return 1;
        }
    }
    return 0;
}

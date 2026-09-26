extern int data_0205e2e4;

int SND_SetActiveSlotSwap(int arg0)
{
    int old = data_0205e2e4;
    data_0205e2e4 = arg0;
    return old;
}

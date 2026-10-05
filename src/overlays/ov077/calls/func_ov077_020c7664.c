extern void PlaySoundChecked(int, int);
extern void QueueSoundCommandForArc(int, int);

void func_ov077_020c7664(int a, int b)
{
    QueueSoundCommandForArc(a, b);
    PlaySoundChecked(a, b);
}

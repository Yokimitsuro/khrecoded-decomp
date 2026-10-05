extern void PlaySoundChecked(int, int);
extern void QueueSoundCommandForArc(int, int);

void func_ov075_020ce820(int a, int b)
{
    QueueSoundCommandForArc(a, b);
    PlaySoundChecked(a, b);
}

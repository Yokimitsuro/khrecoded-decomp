extern void PlaySoundChecked(int, int);
extern void QueueSoundCommandForArc(int, int);

void func_ov076_020ca630(int a, int b)
{
    QueueSoundCommandForArc(a, b);
    PlaySoundChecked(a, b);
}

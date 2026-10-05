typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern void OpenMessageDialog(void *menu, int messageId, int dialogType, int position, int cancelable, va_list args);

void ShowDialogMessage(void *menu, int messageId, int dialogType, int cancelable, ...)
{
    va_list args;

    va_start(args, cancelable);
    OpenMessageDialog(menu, messageId, dialogType, -1, cancelable, args);
}

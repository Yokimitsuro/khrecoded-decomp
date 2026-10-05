extern void func_ov027_020b8b68(void *root, int keys, int runFinisher, int useAlarm);

void UpdateWidgetRootOnly(void *root, int keys)
{
    func_ov027_020b8b68(root, keys, 0, 0);
}

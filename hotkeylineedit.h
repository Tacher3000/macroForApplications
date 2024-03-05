#ifndef HOTKEYLINEEDIT_H
#define HOTKEYLINEEDIT_H

#include<QLineEdit>

class HotKeyLineEdit : public QLineEdit
{
public:
    HotKeyLineEdit();
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // HOTKEYLINEEDIT_H

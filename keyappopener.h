#ifndef KEYAPPOPENER_H
#define KEYAPPOPENER_H

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "hotkeylineedit.h"

class KeyAppOpener : public QObject
{
public:
    KeyAppOpener();
    QGridLayout *getLayout();
private:
    HotKeyLineEdit *testLine;
    QLineEdit *pathLine;
    QPushButton *pathButton;

    QGridLayout *mainLayout;
};

#endif // KEYAPPOPENER_H

#ifndef CENTRALWINDOW_H
#define CENTRALWINDOW_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "createmacrodialog.h"


class CentralWindow : public QWidget
{
    Q_OBJECT
public:
    CentralWindow(QWidget *parent = nullptr);
private:
    QPushButton *test;
    CreateMacroDialog *test2;
};

#endif // CENTRALWINDOW_H

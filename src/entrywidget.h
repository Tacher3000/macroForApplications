#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QJsonObject>

class EntryWidget : public QWidget
{
    Q_OBJECT

public:
    EntryWidget(const QJsonObject &entry, QWidget *parent = nullptr);

private:
    QLabel *iconLabel;
    QLabel *shortcutLabel;
    QLabel *programNameLabel;
    QLabel *titleLabel;
};

#endif // ENTRYWIDGET_H

#include "EntryWidget.h"
#include <QIcon>

EntryWidget::EntryWidget(const QJsonObject &entry, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QPixmap iconPixmap(entry["iconPath"].toString());
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(iconPixmap.scaled(32, 32, Qt::KeepAspectRatio));

    shortcutLabel = new QLabel(entry["keyboardShortcut"].toString(), this);
    programNameLabel = new QLabel(entry["programName"].toString(), this);
    titleLabel = new QLabel(entry["title"].toString(), this);

    layout->addWidget(iconLabel);
    layout->addWidget(shortcutLabel);
    layout->addWidget(programNameLabel);
    layout->addWidget(titleLabel);

    setLayout(layout);
}

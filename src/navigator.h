#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include "basescreensfactory.h"

class BaseFragment;
class QStackedWidget;

class Navigator : public QObject
{
    Q_OBJECT
public:
    explicit Navigator(QStackedWidget *stackedWidget, BaseScreensFactory *factory, QObject *parent = nullptr);
    ~Navigator() override = default;

    void navigateTo(const QString& tag);

private:
    QStackedWidget *stackedWidget;
    BaseScreensFactory *factory;
};

#endif // NAVIGATOR_H

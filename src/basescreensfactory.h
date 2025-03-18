#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include <QObject>

class BaseFragment;

class BaseScreensFactory : public QObject
{
    Q_OBJECT
public:
    explicit BaseScreensFactory(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~BaseScreensFactory() = default;

    virtual BaseFragment* createFragment(const QString& tag) = 0;
};

#endif // BASESCREENSFACTORY_H

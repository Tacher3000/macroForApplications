#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QFrame>

class BaseFragment : public QFrame
{
    Q_OBJECT
public:
    explicit BaseFragment(QWidget *parent = nullptr) : QFrame(parent) {}
    virtual ~BaseFragment() = default;

    virtual void init() = 0;

signals:
    void navigateTo(const QString& tag);
};

#endif // BASEFRAGMENT_H

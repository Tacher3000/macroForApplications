#include "navigator.h"
#include "basefragment.h"
#include "screens.h"
#include <QStackedWidget>

Navigator::Navigator(QStackedWidget *stackedWidget, BaseScreensFactory *factory, QObject *parent)
    : QObject(parent), stackedWidget(stackedWidget), factory(factory)
{
    navigateTo(screens::MAIN_TAG);
}

void Navigator::navigateTo(const QString& tag)
{
    BaseFragment *fragment = factory->createFragment(tag);
    if (fragment) {
        fragment->init();
        stackedWidget->addWidget(fragment);
        stackedWidget->setCurrentWidget(fragment);
        connect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
    }
}
